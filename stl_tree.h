/*
 *
 * Copyright (c) 1996,1997
 * Silicon Graphics Computer Systems, Inc.
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Silicon Graphics makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 * Copyright (c) 1994
 * Hewlett-Packard Company
 *
 * Permission to use, copy, modify, distribute and sell this software
 * and its documentation for any purpose is hereby granted without fee,
 * provided that the above copyright notice appear in all copies and
 * that both that copyright notice and this permission notice appear
 * in supporting documentation.  Hewlett-Packard Company makes no
 * representations about the suitability of this software for any
 * purpose.  It is provided "as is" without express or implied warranty.
 *
 *
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */

#ifndef __SGI_STL_INTERNAL_TREE_H
#define __SGI_STL_INTERNAL_TREE_H

/*

Red-black tree class, designed for use in implementing STL
associative containers (set, multiset, map, and multimap). The
insertion and deletion algorithms are based on those in Cormen,
Leiserson, and Rivest, Introduction to Algorithms (MIT Press, 1990),
except that

(1) the header cell is maintained with links not only to the root
but also to the leftmost node of the tree, to enable constant time
begin(), and to the rightmost node of the tree, to enable linear time
performance when used with the generic set algorithms (set_union,
etc.);

(2) when a node being deleted has two children its successor node is
relinked into its place, rather than copied, so that the only
iterators invalidated are those referring to the deleted node.

*/

#include <stl_algobase.h>
#include <stl_alloc.h>
#include <stl_construct.h>
#include <stl_function.h>

__STL_BEGIN_NAMESPACE 

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma set woff 1375
#endif

typedef bool _Rb_tree_Color_type;
const _Rb_tree_Color_type _S_rb_tree_red = false;           //红色定义为0
const _Rb_tree_Color_type _S_rb_tree_black = true;          //黑色定义为1

struct _Rb_tree_node_base
{
  typedef _Rb_tree_Color_type _Color_type;
  typedef _Rb_tree_node_base* _Base_ptr;                    //红黑树的树节点

  _Color_type _M_color;                                     //节点颜色，非红即黑
  _Base_ptr _M_parent;                                      //RB树的许多操作，必须知道父节点
  _Base_ptr _M_left;                                        //指向左节点
  _Base_ptr _M_right;                                       //指向右节点

  static _Base_ptr _S_minimum(_Base_ptr __x)
  {
    while (__x->_M_left != 0) __x = __x->_M_left;           //一直向左走，就会找到最小值
    return __x;                                             //这是二叉搜索树的特性
  }

  static _Base_ptr _S_maximum(_Base_ptr __x)
  {
    while (__x->_M_right != 0) __x = __x->_M_right;         //一直向左走，就会找到最大值
    return __x;                                             //这也是二叉搜索树的特性
  }
};

template <class _Value>
struct _Rb_tree_node : public _Rb_tree_node_base
{                                         
  typedef _Rb_tree_node<_Value>* _Link_type;                //红黑树节点的封装
  _Value _M_value_field;                                    //节点值
};
                                                            //双层节点结构和双层迭代器结构之间的关系
//_Rb_tree_node继承于_Rb_tree_node_base; _Rb_tree_iterator继承于_Rb_tree_base_iterator;
//在_Rb_tree_base_iterator基类中定义了一个_Rb_tree_node_base基类对象
struct _Rb_tree_base_iterator                               //红黑树的迭代器实现了两层
{                                                           //RB-tree的迭代器是双向迭代器，但不具备随机访问能力
  typedef _Rb_tree_node_base::_Base_ptr _Base_ptr;
  typedef bidirectional_iterator_tag iterator_category;
  typedef ptrdiff_t difference_type;
  _Base_ptr _M_node;                                        //它用来与容器之间产生一个连结关系（make a reference）

  void _M_increment()                                       //operator++会调用此函数
  {
    if (_M_node->_M_right != 0) {                           //如果有右子节点. 状况（1）
      _M_node = _M_node->_M_right;                          //向右走
      while (_M_node->_M_left != 0)                         //然后一直向左子树走到底
        _M_node = _M_node->_M_left;                         //即找到了大1的节点
    }
    else {                                                  //如果没有右子节点. 状况（2）
      _Base_ptr __y = _M_node->_M_parent;                   //找出父节点
      while (_M_node == __y->_M_right) {                    //如果现在的节点本身是一个右子节点
        _M_node = __y;                                      //就一直上溯，直到不为右节点为止
        __y = __y->_M_parent;
      }
      if (_M_node->_M_right != __y)                         //若此时的右节点不等于此时的父节点. 状况（3）
        _M_node = __y;                                      //此时父节点即为答案，下一个更大的元素
    }                                                       //否则此时的node为解答. 状况（4）
  }

  void _M_decrement()                                       //operator--会调用此函数
  {
    if (_M_node->_M_color == _S_rb_tree_red &&              //如果是红节点，而且
        _M_node->_M_parent->_M_parent == _M_node)           //父节点的父节点等于自己. 状况(1)
      _M_node = _M_node->_M_right;                          //右子节点为所求, node为header
    else if (_M_node->_M_left != 0) {                       //如果有左子节点. 状况(2)
      _Base_ptr __y = _M_node->_M_left;                     //令y指向左子节点
      while (__y->_M_right != 0)                            //当y有右子节点是
        __y = __y->_M_right;                                //一直往右节点走到底
      _M_node = __y;                                        //最后答案，如果没有右子节点，y即为所求         
    }
    else {                                                  //既非根节点，也无左子节点. 状况(3)
      _Base_ptr __y = _M_node->_M_parent;                   //找出父节点
      while (_M_node == __y->_M_left) {                     //现在的节点本身是做子节点
        _M_node = __y;                                      //一直交替往下走，直到现在的节点不为左子节点
        __y = __y->_M_parent;
      }
      _M_node = __y;                                        //此时的父节点就为答案
    }
  }
};

template <class _Value, class _Ref, class _Ptr>
struct _Rb_tree_iterator : public _Rb_tree_base_iterator    //RB-tree正规的迭代器
{                                                           //定义5种不同迭代器类型
  typedef _Value value_type;
  typedef _Ref reference;
  typedef _Ptr pointer;
  typedef _Rb_tree_iterator<_Value, _Value&, _Value*>             
    iterator;
  typedef _Rb_tree_iterator<_Value, const _Value&, const _Value*> 
    const_iterator;
  typedef _Rb_tree_iterator<_Value, _Ref, _Ptr>                   
    _Self;
  typedef _Rb_tree_node<_Value>* _Link_type;

  _Rb_tree_iterator() {}
  _Rb_tree_iterator(_Link_type __x) { _M_node = __x; }
  _Rb_tree_iterator(const iterator& __it) { _M_node = __it._M_node; }

  reference operator*() const { return _Link_type(_M_node)->_M_value_field; }
#ifndef __SGI_STL_NO_ARROW_OPERATOR
  pointer operator->() const { return &(operator*()); }
#endif /* __SGI_STL_NO_ARROW_OPERATOR */

  _Self& operator++() { _M_increment(); return *this; }
  _Self operator++(int) {
    _Self __tmp = *this;
    _M_increment();
    return __tmp;
  }
    
  _Self& operator--() { _M_decrement(); return *this; }
  _Self operator--(int) {
    _Self __tmp = *this;
    _M_decrement();
    return __tmp;
  }
};

inline bool operator==(const _Rb_tree_base_iterator& __x,
                       const _Rb_tree_base_iterator& __y) {
  return __x._M_node == __y._M_node;
}

inline bool operator!=(const _Rb_tree_base_iterator& __x,
                       const _Rb_tree_base_iterator& __y) {
  return __x._M_node != __y._M_node;
}

#ifndef __STL_CLASS_PARTIAL_SPECIALIZATION

inline bidirectional_iterator_tag
iterator_category(const _Rb_tree_base_iterator&) {
  return bidirectional_iterator_tag();
}

inline _Rb_tree_base_iterator::difference_type*
distance_type(const _Rb_tree_base_iterator&) {
  return (_Rb_tree_base_iterator::difference_type*) 0;
}

template <class _Value, class _Ref, class _Ptr>
inline _Value* value_type(const _Rb_tree_iterator<_Value, _Ref, _Ptr>&) {
  return (_Value*) 0;
}

#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */

inline void   //全局函数，新节点必须为红色，插入出的父节点也为红色时，就违反了红黑树的规则，
_Rb_tree_rotate_left(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)  //做树形的旋转（以及改变节点的颜色）
{                                                                           //x是旋转点
  _Rb_tree_node_base* __y = __x->_M_right;                                  //令y为旋转点的右子节点
  __x->_M_right = __y->_M_left;
  if (__y->_M_left !=0)
    __y->_M_left->_M_parent = __x;                                          //别忘了回马枪设定父节点
  __y->_M_parent = __x->_M_parent;
                                                                            //令y完全顶替x的地位(必须将x对其父节点的关系完全接收过来)
  if (__x == __root)                                                        //x为根节点
    __root = __y;
  else if (__x == __x->_M_parent->_M_left)                                  //x为其父节点的左子节点
    __x->_M_parent->_M_left = __y;
  else                                                                      //x为其父节点的右子节点
    __x->_M_parent->_M_right = __y;
  __y->_M_left = __x;
  __x->_M_parent = __y;
}

inline void 
_Rb_tree_rotate_right(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root) //树形做右旋转，x为旋转点
{
  _Rb_tree_node_base* __y = __x->_M_left;                                   //y为旋转点的左子节点
  __x->_M_left = __y->_M_right;
  if (__y->_M_right != 0)
    __y->_M_right->_M_parent = __x;                                         //别忘了回马枪设定父节点
  __y->_M_parent = __x->_M_parent;
                                                                            //令y完全顶替x的地位(必须将x对其父节点的关系完全接收过来)
  if (__x == __root)                                                        //x为根节点
    __root = __y;
  else if (__x == __x->_M_parent->_M_right)                                 //x为其父节点的右子节点
    __x->_M_parent->_M_right = __y;
  else                                                                      ////x为其父节点的左子节点
    __x->_M_parent->_M_left = __y;
  __y->_M_right = __x;
  __x->_M_parent = __y;
}

inline void  //_Rb_tree_rebalances是全局函数，重新令树形平衡（改变颜色及旋转树形）
_Rb_tree_rebalance(_Rb_tree_node_base* __x, _Rb_tree_node_base*& __root)  //参数一是新增节点，参数二是root
{
  __x->_M_color = _S_rb_tree_red;                                         //新节点必须为红
  while (__x != __root && __x->_M_parent->_M_color == _S_rb_tree_red) {   //父节点必须为黑，不满足条件进行调整
    if (__x->_M_parent == __x->_M_parent->_M_parent->_M_left) {           //父节点为祖父节点的左子节点
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_right;      //令y为伯父节点
      if (__y && __y->_M_color == _S_rb_tree_red) {                       //伯父节点存在，而且为红
        __x->_M_parent->_M_color = _S_rb_tree_black;                      //更改父节点为黑
        __y->_M_color = _S_rb_tree_black;                                 //更改伯父节点为黑
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;             //更改祖父节点为红
        __x = __x->_M_parent->_M_parent;                                  
      }
      else {                                                              //无伯父节点，或伯父节点为黑
        if (__x == __x->_M_parent->_M_right) {                            //如果新节点为父节点的右子节点
          __x = __x->_M_parent;
          _Rb_tree_rotate_left(__x, __root);                              //进行一次左旋节点操作，第一参数为左旋点
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;                      //改变颜色
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;
        _Rb_tree_rotate_right(__x->_M_parent->_M_parent, __root);         //进行一次右旋节点操作，第一参数为右旋点
      }
    }
    else {                                                                //父节点为祖父节点的右子节点
      _Rb_tree_node_base* __y = __x->_M_parent->_M_parent->_M_left;       //令y为伯父节点
      if (__y && __y->_M_color == _S_rb_tree_red) {                       //如果有伯父节点，而且为红
        __x->_M_parent->_M_color = _S_rb_tree_black;                      //更改父节点为黑
        __y->_M_color = _S_rb_tree_black;                                 //更改伯父节点为黑
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;             //更改祖父节点为红
        __x = __x->_M_parent->_M_parent;                                  //准备继续往上层检查
      }
      else {                                                              //无伯父节点，或伯父节点为黑
        if (__x == __x->_M_parent->_M_left) {                             //如果新节点为父节点的左子节点
          __x = __x->_M_parent;                                           //x等于父节点
          _Rb_tree_rotate_right(__x, __root);                             //进行一次右旋节点操作，第一参数为右旋点
        }
        __x->_M_parent->_M_color = _S_rb_tree_black;                      //改变父节点位置元素的颜色为黑
        __x->_M_parent->_M_parent->_M_color = _S_rb_tree_red;             //祖父节点的颜色为红
        _Rb_tree_rotate_left(__x->_M_parent->_M_parent, __root);          //进行一次左旋节点操作，第一参数为左旋点
      }                                                                   //这个树形调整就是由上而下的程序
    }                                                                     //有时候需要改变颜色，有时候需要做单旋，有时候需要做双旋
  }                                                                       //有时候做左旋，有时候做右旋
  __root->_M_color = _S_rb_tree_black;                                    //但根的颜色始终是黑色
}

inline _Rb_tree_node_base*
_Rb_tree_rebalance_for_erase(_Rb_tree_node_base* __z,
                             _Rb_tree_node_base*& __root,
                             _Rb_tree_node_base*& __leftmost,
                             _Rb_tree_node_base*& __rightmost)
{
  _Rb_tree_node_base* __y = __z;
  _Rb_tree_node_base* __x = 0;
  _Rb_tree_node_base* __x_parent = 0;
  if (__y->_M_left == 0)     // __z has at most one non-null child. y == z.
    __x = __y->_M_right;     // __x might be null.
  else
    if (__y->_M_right == 0)  // __z has exactly one non-null child. y == z.
      __x = __y->_M_left;    // __x is not null.
    else {                   // __z has two non-null children.  Set __y to
      __y = __y->_M_right;   //   __z's successor.  __x might be null.
      while (__y->_M_left != 0)
        __y = __y->_M_left;
      __x = __y->_M_right;
    }
  if (__y != __z) {          // relink y in place of z.  y is z's successor
    __z->_M_left->_M_parent = __y; 
    __y->_M_left = __z->_M_left;
    if (__y != __z->_M_right) {
      __x_parent = __y->_M_parent;
      if (__x) __x->_M_parent = __y->_M_parent;
      __y->_M_parent->_M_left = __x;      // __y must be a child of _M_left
      __y->_M_right = __z->_M_right;
      __z->_M_right->_M_parent = __y;
    }
    else
      __x_parent = __y;  
    if (__root == __z)
      __root = __y;
    else if (__z->_M_parent->_M_left == __z)
      __z->_M_parent->_M_left = __y;
    else 
      __z->_M_parent->_M_right = __y;
    __y->_M_parent = __z->_M_parent;
    __STD::swap(__y->_M_color, __z->_M_color);
    __y = __z;
    // __y now points to node to be actually deleted
  }
  else {                        // __y == __z
    __x_parent = __y->_M_parent;
    if (__x) __x->_M_parent = __y->_M_parent;   
    if (__root == __z)
      __root = __x;
    else 
      if (__z->_M_parent->_M_left == __z)
        __z->_M_parent->_M_left = __x;
      else
        __z->_M_parent->_M_right = __x;
    if (__leftmost == __z) 
      if (__z->_M_right == 0)        // __z->_M_left must be null also
        __leftmost = __z->_M_parent;
    // makes __leftmost == _M_header if __z == __root
      else
        __leftmost = _Rb_tree_node_base::_S_minimum(__x);
    if (__rightmost == __z)  
      if (__z->_M_left == 0)         // __z->_M_right must be null also
        __rightmost = __z->_M_parent;  
    // makes __rightmost == _M_header if __z == __root
      else                      // __x == __z->_M_left
        __rightmost = _Rb_tree_node_base::_S_maximum(__x);
  }
  if (__y->_M_color != _S_rb_tree_red) { 
    while (__x != __root && (__x == 0 || __x->_M_color == _S_rb_tree_black))
      if (__x == __x_parent->_M_left) {
        _Rb_tree_node_base* __w = __x_parent->_M_right;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rb_tree_rotate_left(__x_parent, __root);
          __w = __x_parent->_M_right;
        }
        if ((__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black) &&
            (__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_right == 0 || 
              __w->_M_right->_M_color == _S_rb_tree_black) {
            if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rb_tree_rotate_right(__w, __root);
            __w = __x_parent->_M_right;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
          _Rb_tree_rotate_left(__x_parent, __root);
          break;
        }
      } else {                  // same as above, with _M_right <-> _M_left.
        _Rb_tree_node_base* __w = __x_parent->_M_left;
        if (__w->_M_color == _S_rb_tree_red) {
          __w->_M_color = _S_rb_tree_black;
          __x_parent->_M_color = _S_rb_tree_red;
          _Rb_tree_rotate_right(__x_parent, __root);
          __w = __x_parent->_M_left;
        }
        if ((__w->_M_right == 0 || 
             __w->_M_right->_M_color == _S_rb_tree_black) &&
            (__w->_M_left == 0 || 
             __w->_M_left->_M_color == _S_rb_tree_black)) {
          __w->_M_color = _S_rb_tree_red;
          __x = __x_parent;
          __x_parent = __x_parent->_M_parent;
        } else {
          if (__w->_M_left == 0 || 
              __w->_M_left->_M_color == _S_rb_tree_black) {
            if (__w->_M_right) __w->_M_right->_M_color = _S_rb_tree_black;
            __w->_M_color = _S_rb_tree_red;
            _Rb_tree_rotate_left(__w, __root);
            __w = __x_parent->_M_left;
          }
          __w->_M_color = __x_parent->_M_color;
          __x_parent->_M_color = _S_rb_tree_black;
          if (__w->_M_left) __w->_M_left->_M_color = _S_rb_tree_black;
          _Rb_tree_rotate_right(__x_parent, __root);
          break;
        }
      }
    if (__x) __x->_M_color = _S_rb_tree_black;
  }
  return __y;
}

// Base class to encapsulate the differences between old SGI-style
// allocators and standard-conforming allocators.  In order to avoid
// having an empty base class, we arbitrarily move one of rb_tree's
// data members into the base class.

#ifdef __STL_USE_STD_ALLOCATORS

// _Base for general standard-conforming allocators.
template <class _Tp, class _Alloc, bool _S_instanceless>
class _Rb_tree_alloc_base {
public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;
  allocator_type get_allocator() const { return _M_node_allocator; }

  _Rb_tree_alloc_base(const allocator_type& __a)
    : _M_node_allocator(__a), _M_header(0) {}

protected:
  typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::allocator_type
           _M_node_allocator;
  _Rb_tree_node<_Tp>* _M_header;

  _Rb_tree_node<_Tp>* _M_get_node() 
    { return _M_node_allocator.allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p) 
    { _M_node_allocator.deallocate(__p, 1); }
};

// Specialization for instanceless allocators.
template <class _Tp, class _Alloc>
class _Rb_tree_alloc_base<_Tp, _Alloc, true> {
public:
  typedef typename _Alloc_traits<_Tp, _Alloc>::allocator_type allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_alloc_base(const allocator_type&) : _M_header(0) {}

protected:
  _Rb_tree_node<_Tp>* _M_header;

  typedef typename _Alloc_traits<_Rb_tree_node<_Tp>, _Alloc>::_Alloc_type
          _Alloc_type;

  _Rb_tree_node<_Tp>* _M_get_node()
    { return _Alloc_type::allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p)
    { _Alloc_type::deallocate(__p, 1); }
};

template <class _Tp, class _Alloc>
struct _Rb_tree_base
  : public _Rb_tree_alloc_base<_Tp, _Alloc,
                               _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
{
  typedef _Rb_tree_alloc_base<_Tp, _Alloc,
                              _Alloc_traits<_Tp, _Alloc>::_S_instanceless>
          _Base;
  typedef typename _Base::allocator_type allocator_type;

  _Rb_tree_base(const allocator_type& __a) 
    : _Base(__a) { _M_header = _M_get_node(); }
  ~_Rb_tree_base() { _M_put_node(_M_header); }

};

#else /* __STL_USE_STD_ALLOCATORS */

template <class _Tp, class _Alloc>
struct _Rb_tree_base
{
  typedef _Alloc allocator_type;
  allocator_type get_allocator() const { return allocator_type(); }

  _Rb_tree_base(const allocator_type&) 
    : _M_header(0) { _M_header = _M_get_node(); }
  ~_Rb_tree_base() { _M_put_node(_M_header); }

protected:
  _Rb_tree_node<_Tp>* _M_header;                                    //在基类中定义的header，这是一个实现上的技巧

  typedef simple_alloc<_Rb_tree_node<_Tp>, _Alloc> _Alloc_type;     //每次可恰恰配置一个节点
                                                                    //RB-tree的构造方式有两种，一种是以现有的RB-tree复制一个新的RB-tree
  _Rb_tree_node<_Tp>* _M_get_node()                                 //另一种是产生一棵空空如也的树
    { return _Alloc_type::allocate(1); }
  void _M_put_node(_Rb_tree_node<_Tp>* __p)
    { _Alloc_type::deallocate(__p, 1); }
};

#endif /* __STL_USE_STD_ALLOCATORS */

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
class _Rb_tree : protected _Rb_tree_base<_Value, _Alloc> {
  typedef _Rb_tree_base<_Value, _Alloc> _Base;
protected:
  typedef _Rb_tree_node_base* _Base_ptr;
  typedef _Rb_tree_node<_Value> _Rb_tree_node;
  typedef _Rb_tree_Color_type _Color_type;
public:
  typedef _Key key_type;
  typedef _Value value_type;
  typedef value_type* pointer;
  typedef const value_type* const_pointer;
  typedef value_type& reference;
  typedef const value_type& const_reference;
  typedef _Rb_tree_node* _Link_type;
  typedef size_t size_type;
  typedef ptrdiff_t difference_type;

  typedef typename _Base::allocator_type allocator_type;
  allocator_type get_allocator() const { return _Base::get_allocator(); }

protected:
#ifdef __STL_USE_NAMESPACES
  using _Base::_M_get_node;
  using _Base::_M_put_node;
  using _Base::_M_header;
#endif /* __STL_USE_NAMESPACES */

protected:

  _Link_type _M_create_node(const value_type& __x)
  {
    _Link_type __tmp = _M_get_node();                           //配置空间
    __STL_TRY {
      construct(&__tmp->_M_value_field, __x);                   //构造内容
    }
    __STL_UNWIND(_M_put_node(__tmp));
    return __tmp;
  }

  _Link_type _M_clone_node(_Link_type __x)                      //复制一个节点的值和颜色
  {
    _Link_type __tmp = _M_create_node(__x->_M_value_field);
    __tmp->_M_color = __x->_M_color;
    __tmp->_M_left = 0;
    __tmp->_M_right = 0;
    return __tmp;
  }

  void destroy_node(_Link_type __p)
  {
    destroy(&__p->_M_value_field);                              //析构内容
    _M_put_node(__p);                                           //释放内存
  }

protected:                                                      //RB-tree只有三个数据表现
  size_type _M_node_count; // keeps track of size of tree       //追踪记录树的大小（节点数量）
  _Compare _M_key_compare;                                      //节点间的键值大小比较准则，应该会是一个函数对象
                                                                //一下函数用来方便取得节点x的成员
  _Link_type& _M_root() const                                   //取根节点
    { return (_Link_type&) _M_header->_M_parent; }
  _Link_type& _M_leftmost() const                               //取最左边的节点
    { return (_Link_type&) _M_header->_M_left; }
  _Link_type& _M_rightmost() const                              //取最右边的节点
    { return (_Link_type&) _M_header->_M_right; }

  static _Link_type& _S_left(_Link_type __x)                    //取x节点的左子节点
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Link_type __x)                   //取x节点的右子节点
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Link_type __x)                  //取x节点的父节点
    { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Link_type __x)                     //取x节点的存储的值  
    { return __x->_M_value_field; }
  static const _Key& _S_key(_Link_type __x)                     //取x节点的键值 
    { return _KeyOfValue()(_S_value(__x)); }
  static _Color_type& _S_color(_Link_type __x)                  //取x节点的颜色   
    { return (_Color_type&)(__x->_M_color); }

  static _Link_type& _S_left(_Base_ptr __x)                     //基类指针的成员
    { return (_Link_type&)(__x->_M_left); }
  static _Link_type& _S_right(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_right); }
  static _Link_type& _S_parent(_Base_ptr __x)
    { return (_Link_type&)(__x->_M_parent); }
  static reference _S_value(_Base_ptr __x)
    { return ((_Link_type)__x)->_M_value_field; }
  static const _Key& _S_key(_Base_ptr __x)
    { return _KeyOfValue()(_S_value(_Link_type(__x)));} 
  static _Color_type& _S_color(_Base_ptr __x)
    { return (_Color_type&)(_Link_type(__x)->_M_color); }

  static _Link_type _S_minimum(_Link_type __x)                  //求极小值，调用基类函数 
    { return (_Link_type)  _Rb_tree_node_base::_S_minimum(__x); }

  static _Link_type _S_maximum(_Link_type __x)                  //求极大值，调用基类函数
    { return (_Link_type) _Rb_tree_node_base::_S_maximum(__x); }

public:
  typedef _Rb_tree_iterator<value_type, reference, pointer> iterator;
  typedef _Rb_tree_iterator<value_type, const_reference, const_pointer> 
          const_iterator;

#ifdef __STL_CLASS_PARTIAL_SPECIALIZATION
  typedef reverse_iterator<const_iterator> const_reverse_iterator;
  typedef reverse_iterator<iterator> reverse_iterator;
#else /* __STL_CLASS_PARTIAL_SPECIALIZATION */
  typedef reverse_bidirectional_iterator<iterator, value_type, reference,
                                         difference_type>
          reverse_iterator; 
  typedef reverse_bidirectional_iterator<const_iterator, value_type,
                                         const_reference, difference_type>
          const_reverse_iterator;
#endif /* __STL_CLASS_PARTIAL_SPECIALIZATION */ 

private:
  iterator _M_insert(_Base_ptr __x, _Base_ptr __y, const value_type& __v);
  _Link_type _M_copy(_Link_type __x, _Link_type __p);
  void _M_erase(_Link_type __x);

public:
                                // allocation/deallocation，构造和析构函数
  _Rb_tree()
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare()
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp)
    : _Base(allocator_type()), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Compare& __comp, const allocator_type& __a)
    : _Base(__a), _M_node_count(0), _M_key_compare(__comp) 
    { _M_empty_initialize(); }

  _Rb_tree(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x) 
    : _Base(__x.get_allocator()),
      _M_node_count(0), _M_key_compare(__x._M_key_compare)
  { 
    if (__x._M_root() == 0)
      _M_empty_initialize();
    else {
      _S_color(_M_header) = _S_rb_tree_red;
      _M_root() = _M_copy(__x._M_root(), _M_header);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
    }
    _M_node_count = __x._M_node_count;
  }
  ~_Rb_tree() { clear(); }
  _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
  operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x);

private:
  void _M_empty_initialize() {
    _S_color(_M_header) = _S_rb_tree_red; // used to distinguish header from 
                                          // __root, in iterator.operator++
    _M_root() = 0;
    _M_leftmost() = _M_header;            //令header的左子节点为自己
    _M_rightmost() = _M_header;           //令header的右子节点为自己
  }

public:    
                                // accessors:
  _Compare key_comp() const { return _M_key_compare; }
  iterator begin() { return _M_leftmost(); }                      //红黑树的起头我最左（最小）节点处
  const_iterator begin() const { return _M_leftmost(); }
  iterator end() { return _M_header; }                            //RB-tree的终点为header所指处
  const_iterator end() const { return _M_header; }
  reverse_iterator rbegin() { return reverse_iterator(end()); }
  const_reverse_iterator rbegin() const { 
    return const_reverse_iterator(end()); 
  }
  reverse_iterator rend() { return reverse_iterator(begin()); }
  const_reverse_iterator rend() const { 
    return const_reverse_iterator(begin());
  } 
  bool empty() const { return _M_node_count == 0; }
  size_type size() const { return _M_node_count; }
  size_type max_size() const { return size_type(-1); }

  void swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __t) {
    __STD::swap(_M_header, __t._M_header);
    __STD::swap(_M_node_count, __t._M_node_count);
    __STD::swap(_M_key_compare, __t._M_key_compare);
  }
    
public:
                                // insert/erase
  pair<iterator,bool> insert_unique(const value_type& __x);
  iterator insert_equal(const value_type& __x);
  // 将x插入到RB-tree中，保持节点值独一无二
  iterator insert_unique(iterator __position, const value_type& __x);
  iterator insert_equal(iterator __position, const value_type& __x);  // 将x插入到RB-tree中，允许节点值重复

#ifdef __STL_MEMBER_TEMPLATES  
  template <class _InputIterator>
  void insert_unique(_InputIterator __first, _InputIterator __last);
  template <class _InputIterator>
  void insert_equal(_InputIterator __first, _InputIterator __last);
#else /* __STL_MEMBER_TEMPLATES */
  void insert_unique(const_iterator __first, const_iterator __last);
  void insert_unique(const value_type* __first, const value_type* __last);
  void insert_equal(const_iterator __first, const_iterator __last);
  void insert_equal(const value_type* __first, const value_type* __last);
#endif /* __STL_MEMBER_TEMPLATES */

  void erase(iterator __position);
  size_type erase(const key_type& __x);
  void erase(iterator __first, iterator __last);
  void erase(const key_type* __first, const key_type* __last);
  void clear() {
    if (_M_node_count != 0) {
      _M_erase(_M_root());
      _M_leftmost() = _M_header;
      _M_root() = 0;
      _M_rightmost() = _M_header;
      _M_node_count = 0;
    }
  }      

public:
                                // set operations:
  iterator find(const key_type& __x);
  const_iterator find(const key_type& __x) const;
  size_type count(const key_type& __x) const;
  iterator lower_bound(const key_type& __x);
  const_iterator lower_bound(const key_type& __x) const;
  iterator upper_bound(const key_type& __x);
  const_iterator upper_bound(const key_type& __x) const;
  pair<iterator,iterator> equal_range(const key_type& __x);
  pair<const_iterator, const_iterator> equal_range(const key_type& __x) const;

public:
                                // Debugging.
  bool __rb_verify() const;
};

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator==(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return __x.size() == __y.size() &&
         equal(__x.begin(), __x.end(), __y.begin());
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator<(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  return lexicographical_compare(__x.begin(), __x.end(), 
                                 __y.begin(), __y.end());
}

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator!=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x == __y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator>(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
          const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return __y < __x;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator<=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__y < __x);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline bool 
operator>=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
           const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y) {
  return !(__x < __y);
}


template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void 
swap(_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x, 
     _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __y)
{
  __x.swap(__y);
}

#endif /* __STL_FUNCTION_TMPL_PARTIAL_ORDER */


template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::operator=(const _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>& __x)
{
  if (this != &__x) {
                                // Note that _Key may be a constant type.
    clear();
    _M_node_count = 0;
    _M_key_compare = __x._M_key_compare;        
    if (__x._M_root() == 0) {
      _M_root() = 0;
      _M_leftmost() = _M_header;
      _M_rightmost() = _M_header;
    }
    else {
      _M_root() = _M_copy(__x._M_root(), _M_header);
      _M_leftmost() = _S_minimum(_M_root());
      _M_rightmost() = _S_maximum(_M_root());
      _M_node_count = __x._M_node_count;
    }
  }
  return *this;
}

template <class _Key, class _Value, class _KeyOfValue,                //真正执行插入操作的程序
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>                     //参数x为新值插入点，参数y为插入点的父节点，参数v为新值
  ::_M_insert(_Base_ptr __x_, _Base_ptr __y_, const _Value& __v)
{
  _Link_type __x = (_Link_type) __x_;
  _Link_type __y = (_Link_type) __y_;
  _Link_type __z;

  if (__y == _M_header || __x != 0 ||                                 //_M_key_compare是键值比较准则，应该是一个函数对象function object
      _M_key_compare(_KeyOfValue()(__v), _S_key(__y))) {
    __z = _M_create_node(__v);                                        //产生一个新节点 
    _S_left(__y) = __z;               // also makes _M_leftmost() = __z  这使得当y为header时，leftmost() = z
                                      //    when __y == _M_header
    if (__y == _M_header) {
      _M_root() = __z;
      _M_rightmost() = __z;
    }
    else if (__y == _M_leftmost())                                    //如果y是最左节点
      _M_leftmost() = __z;   // maintain _M_leftmost() pointing to min node 维护leftmost(),使它永远指向最左节点
  }
  else {
    __z = _M_create_node(__v);                                        //产生一个新节点
    _S_right(__y) = __z;                                              //令新节点成为插入节点的父节点y的右子节点
    if (__y == _M_rightmost())
      _M_rightmost() = __z;  // maintain _M_rightmost() pointing to max node 维护rightmost(), 使他永远指向最右节点
  }
  _S_parent(__z) = __y;                                               //设定新节点的父节点
  _S_left(__z) = 0;                                                   //设定新节点的左子节点
  _S_right(__z) = 0;                                                  //设定新节点的右子节点
  _Rb_tree_rebalance(__z, _M_header->_M_parent);                      //新节点的颜色在_Rb_tree_rebalance中设定（并调整），参数一是新增节点，参数二是root
  ++_M_node_count;                                                    //节点数累加
  return iterator(__z);                                               //返回一个迭代器指向一个新节点
}

template <class _Key, class _Value, class _KeyOfValue,                  //插入新值，节点键值允许重复
          class _Compare, class _Alloc>                                 //返回一个迭代器，指向一个RB-tree迭代器，指向新增节点 
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::insert_equal(const _Value& __v)
{
  _Link_type __y = _M_header;
  _Link_type __x = _M_root();                                           //从根节点开始   
  while (__x != 0) {                                                    //从根节点开始，往下寻找适当的插入点  
    __y = __x;
    __x = _M_key_compare(_KeyOfValue()(__v), _S_key(__x)) ?             //遇大则往左，遇小或等于则往右，_KeyOfValue是一个仿生函数
            _S_left(__x) : _S_right(__x);
  }
  return _M_insert(__x, __y, __v);                                      //x为新值插入点，y为插入点的父节点，v为新值
}


template <class _Key, class _Value, class _KeyOfValue,                  //插入新值，节点不允许重复，若重复则插入无效
          class _Compare, class _Alloc>                                 //返回的是一个pair，第一个元素是RB-tree的跌代器，指向新增节点
pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator, 
     bool>                                                              //第二个元素表示插入是否成功
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::insert_unique(const _Value& __v)
{
  _Link_type __y = _M_header;
  _Link_type __x = _M_root();                                           //从根节点开始
  bool __comp = true;
  while (__x != 0) {                                                    //从根节点开始，往下寻找适当的插入点
    __y = __x;
    __comp = _M_key_compare(_KeyOfValue()(__v), _S_key(__x));           //v键值是否小于目前节点的键值
    __x = __comp ? _S_left(__x) : _S_right(__x);                        //遇大则往左，遇小或等于则往右
  }                                                                     //离开循环后，y所指就是插入点的父节点（此时它必须为叶节点）
  iterator __j = iterator(__y);                                         //令迭代器j指向插入节点的父节点y
  if (__comp)                                                           //如果离开while是camp为真（表示遇大，将插入于左侧）
    if (__j == begin())                                                 //如果插入节点的父节点为最左节点  
      return pair<iterator,bool>(_M_insert(__x, __y, __v), true);       //则返回;x为新值插入点，y为插入点的父节点，v为新值
    else                                                                //否则插入点的父节点不是最左节点
      --__j;                                                            //调整j，回头准备测试……
  if (_M_key_compare(_S_key(__j._M_node), _KeyOfValue()(__v)))          //新键值不与已存在的节点键值重复，于是安排插入操作
    return pair<iterator,bool>(_M_insert(__x, __y, __v), true);         //x为新值插入点，y为插入点的父节点，v为新值
  return pair<iterator,bool>(__j, false);                               //否则，新值一定与树中键值重复，那么就不该插入新值
}


template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>::iterator 
_Rb_tree<_Key, _Val, _KeyOfValue, _Compare, _Alloc>
  ::insert_unique(iterator __position, const _Val& __v)
{
  if (__position._M_node == _M_header->_M_left) { // begin()
    if (size() > 0 && 
        _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      return insert_unique(__v).first;
  } else if (__position._M_node == _M_header) { // end()
    if (_M_key_compare(_S_key(_M_rightmost()), _KeyOfValue()(__v)))
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_unique(__v).first;
  } else {
    iterator __before = __position;
    --__before;
    if (_M_key_compare(_S_key(__before._M_node), _KeyOfValue()(__v)) 
        && _M_key_compare(_KeyOfValue()(__v), _S_key(__position._M_node))) {
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v); 
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      return insert_unique(__v).first;
  }
}

template <class _Key, class _Val, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>::iterator        
_Rb_tree<_Key,_Val,_KeyOfValue,_Compare,_Alloc>                                          
  ::insert_equal(iterator __position, const _Val& __v)
{
  if (__position._M_node == _M_header->_M_left) { // begin()              
    if (size() > 0 && 
        !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v)))
      return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    else
      return insert_equal(__v);
  } else if (__position._M_node == _M_header) {// end()
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(_M_rightmost())))
      return _M_insert(0, _M_rightmost(), __v);
    else
      return insert_equal(__v);
  } else {
    iterator __before = __position;
    --__before;
    if (!_M_key_compare(_KeyOfValue()(__v), _S_key(__before._M_node))
        && !_M_key_compare(_S_key(__position._M_node), _KeyOfValue()(__v))) {
      if (_S_right(__before._M_node) == 0)
        return _M_insert(0, __before._M_node, __v); 
      else
        return _M_insert(__position._M_node, __position._M_node, __v);
    // first argument just needs to be non-null 
    } else
      return insert_equal(__v);
  }
}

#ifdef __STL_MEMBER_TEMPLATES  

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
  template<class _II>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(_II __first, _II __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc> 
  template<class _II>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(_II __first, _II __last) {
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

#else /* __STL_MEMBER_TEMPLATES */

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(const _Val* __first, const _Val* __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_equal(const_iterator __first, const_iterator __last)
{
  for ( ; __first != __last; ++__first)
    insert_equal(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void 
_Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(const _Val* __first, const _Val* __last)
{
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

template <class _Key, class _Val, class _KoV, class _Cmp, class _Alloc>
void _Rb_tree<_Key,_Val,_KoV,_Cmp,_Alloc>
  ::insert_unique(const_iterator __first, const_iterator __last)
{
  for ( ; __first != __last; ++__first)
    insert_unique(*__first);
}

#endif /* __STL_MEMBER_TEMPLATES */
         
template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __position)
{
  _Link_type __y = 
    (_Link_type) _Rb_tree_rebalance_for_erase(__position._M_node,
                                              _M_header->_M_parent,
                                              _M_header->_M_left,
                                              _M_header->_M_right);
  destroy_node(__y);
  --_M_node_count;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::erase(const _Key& __x)
{
  pair<iterator,iterator> __p = equal_range(__x);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  erase(__p.first, __p.second);
  return __n;
}

template <class _Key, class _Val, class _KoV, class _Compare, class _Alloc>
typename _Rb_tree<_Key, _Val, _KoV, _Compare, _Alloc>::_Link_type 
_Rb_tree<_Key,_Val,_KoV,_Compare,_Alloc>
  ::_M_copy(_Link_type __x, _Link_type __p)
{
                        // structural copy.  __x and __p must be non-null.
  _Link_type __top = _M_clone_node(__x);
  __top->_M_parent = __p;
 
  __STL_TRY {
    if (__x->_M_right)
      __top->_M_right = _M_copy(_S_right(__x), __top);
    __p = __top;
    __x = _S_left(__x);

    while (__x != 0) {
      _Link_type __y = _M_clone_node(__x);
      __p->_M_left = __y;
      __y->_M_parent = __p;
      if (__x->_M_right)
        __y->_M_right = _M_copy(_S_right(__x), __y);
      __p = __y;
      __x = _S_left(__x);
    }
  }
  __STL_UNWIND(_M_erase(__top));

  return __top;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::_M_erase(_Link_type __x)
{
                                // erase without rebalancing
  while (__x != 0) {
    _M_erase(_S_right(__x));
    _Link_type __y = _S_left(__x);
    destroy_node(__x);
    __x = __y;
  }
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(iterator __first, iterator __last)
{
  if (__first == begin() && __last == end())
    clear();
  else
    while (__first != __last) erase(__first++);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
void _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::erase(const _Key* __first, const _Key* __last) 
{
  while (__first != __last) erase(*__first++);
}

template <class _Key, class _Value, class _KeyOfValue,                    //寻找RB树中是否有键值为k的节点
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k)
{
  _Link_type __y = _M_header;      // Last node which is not less than __k. 
  _Link_type __x = _M_root();      // Current node. 

  while (__x != 0)                                                        //_M_key_compare是一个节点键值大小比较准则，应该是一个函数对象
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);                            //注意这里的语法，表示x键值小于k，遇到小值就往左走
    else
      __x = _S_right(__x);                                      //否则，x键值小于k，遇到小值就向右走

  iterator __j = iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ? 
     end() : __j;                                               //返回节点
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::find(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) {
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);
  }
  const_iterator __j = const_iterator(__y);   
  return (__j == end() || _M_key_compare(__k, _S_key(__j._M_node))) ?
    end() : __j;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::size_type 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::count(const _Key& __k) const
{
  pair<const_iterator, const_iterator> __p = equal_range(__k);
  size_type __n = 0;
  distance(__p.first, __p.second, __n);
  return __n;
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::lower_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is not less than __k. */
  _Link_type __x = _M_root(); /* Current node. */

  while (__x != 0) 
    if (!_M_key_compare(_S_key(__x), __k))
      __y = __x, __x = _S_left(__x);
    else
      __x = _S_right(__x);

  return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k)
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x)))
       __y = __x, __x = _S_left(__x);
     else
       __x = _S_right(__x);

   return iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::const_iterator 
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::upper_bound(const _Key& __k) const
{
  _Link_type __y = _M_header; /* Last node which is greater than __k. */
  _Link_type __x = _M_root(); /* Current node. */

   while (__x != 0) 
     if (_M_key_compare(__k, _S_key(__x)))
       __y = __x, __x = _S_left(__x);
     else
       __x = _S_right(__x);

   return const_iterator(__y);
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
inline 
pair<typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator,
     typename _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::iterator>
_Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>
  ::equal_range(const _Key& __k)
{
  return pair<iterator, iterator>(lower_bound(__k), upper_bound(__k));
}

template <class _Key, class _Value, class _KoV, class _Compare, class _Alloc>
inline 
pair<typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator,
     typename _Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>::const_iterator>
_Rb_tree<_Key, _Value, _KoV, _Compare, _Alloc>
  ::equal_range(const _Key& __k) const
{
  return pair<const_iterator,const_iterator>(lower_bound(__k),
                                             upper_bound(__k));
}

inline int 
__black_count(_Rb_tree_node_base* __node, _Rb_tree_node_base* __root)
{
  if (__node == 0)
    return 0;
  else {
    int __bc = __node->_M_color == _S_rb_tree_black ? 1 : 0;
    if (__node == __root)
      return __bc;
    else
      return __bc + __black_count(__node->_M_parent, __root);
  }
}

template <class _Key, class _Value, class _KeyOfValue, 
          class _Compare, class _Alloc>
bool _Rb_tree<_Key,_Value,_KeyOfValue,_Compare,_Alloc>::__rb_verify() const
{
  if (_M_node_count == 0 || begin() == end())
    return _M_node_count == 0 && begin() == end() &&
      _M_header->_M_left == _M_header && _M_header->_M_right == _M_header;
  
  int __len = __black_count(_M_leftmost(), _M_root());
  for (const_iterator __it = begin(); __it != end(); ++__it) {
    _Link_type __x = (_Link_type) __it._M_node;
    _Link_type __L = _S_left(__x);
    _Link_type __R = _S_right(__x);

    if (__x->_M_color == _S_rb_tree_red)
      if ((__L && __L->_M_color == _S_rb_tree_red) ||
          (__R && __R->_M_color == _S_rb_tree_red))
        return false;

    if (__L && _M_key_compare(_S_key(__x), _S_key(__L)))
      return false;
    if (__R && _M_key_compare(_S_key(__R), _S_key(__x)))
      return false;

    if (!__L && !__R && __black_count(__x, _M_root()) != __len)
      return false;
  }

  if (_M_leftmost() != _Rb_tree_node_base::_S_minimum(_M_root()))
    return false;
  if (_M_rightmost() != _Rb_tree_node_base::_S_maximum(_M_root()))
    return false;

  return true;
}

// Class rb_tree is not part of the C++ standard.  It is provided for
// compatibility with the HP STL.

template <class _Key, class _Value, class _KeyOfValue, class _Compare,
          class _Alloc = __STL_DEFAULT_ALLOCATOR(_Value) >
struct rb_tree : public _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc>
{
  typedef _Rb_tree<_Key, _Value, _KeyOfValue, _Compare, _Alloc> _Base;
  typedef typename _Base::allocator_type allocator_type;

  rb_tree(const _Compare& __comp = _Compare(),
          const allocator_type& __a = allocator_type())
    : _Base(__comp, __a) {}
  
  ~rb_tree() {}
};

#if defined(__sgi) && !defined(__GNUC__) && (_MIPS_SIM != _MIPS_SIM_ABI32)
#pragma reset woff 1375
#endif

__STL_END_NAMESPACE 

#endif /* __SGI_STL_INTERNAL_TREE_H */

// Local Variables:
// mode:C++
// End: