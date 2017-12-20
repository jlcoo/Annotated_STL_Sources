/*
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
 */

/* NOTE: This is an internal header file, included by other STL headers.
 *   You should not attempt to use it directly.
 */


#ifndef __SGI_STL_INTERNAL_NUMERIC_H
#define __SGI_STL_INTERNAL_NUMERIC_H

__STL_BEGIN_NAMESPACE

template <class _InputIterator, class _Tp>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  for ( ; __first != __last; ++__first)                   //将每个元素加到初值init身上
    __init = __init + *__first;         
  return __init;
}

template <class _InputIterator, class _Tp, class _BinaryOperation>
_Tp accumulate(_InputIterator __first, _InputIterator __last, _Tp __init,
               _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  for ( ; __first != __last; ++__first)
    __init = __binary_op(__init, *__first);               //对第一个元素执行二元操作，二元操作符不必满足交换律(commutative)和结合律(associative)
  return __init;                                          //一定得提供一个初始值init
}                                                         //求[first, last)中所有数值的总和，应该将init设为0

template <class _InputIterator1, class _InputIterator2, class _Tp>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init)
{
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  for ( ; __first1 != __last1; ++__first1, ++__first2)    //以第一序列的元素个数为据, 将两个序列都走一遍
    __init = __init + (*__first1 * *__first2);            //执行两个序列的一般内积
  return __init;
}

template <class _InputIterator1, class _InputIterator2, class _Tp,
          class _BinaryOperation1, class _BinaryOperation2>
_Tp inner_product(_InputIterator1 __first1, _InputIterator1 __last1,
                  _InputIterator2 __first2, _Tp __init, 
                  _BinaryOperation1 __binary_op1,
                  _BinaryOperation2 __binary_op2)
{
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  __STL_REQUIRES(_InputIterator2, _InputIterator);
  for ( ; __first1 != __last1; ++__first1, ++__first2)
    __init = __binary_op1(__init, __binary_op2(*__first1, *__first2)); //以外界提供的仿函数取代第一版本中的operator* 和operator+
  return __init;                        //如果想计算两个vectors的一般内积，应该将init设为0
}

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last,
              _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __value + *__first;       //前n个元素的总和
    *++__result = __value;              //指定给目的端
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first));
}
// __partial_sum计算局部总和
template <class _InputIterator, class _OutputIterator, class _Tp,
          class _BinaryOperation>
_OutputIterator 
__partial_sum(_InputIterator __first, _InputIterator __last, 
              _OutputIterator __result, _Tp*, _BinaryOperation __binary_op)
{
  _Tp __value = *__first;
  while (++__first != __last) {
    __value = __binary_op(__value, *__first);     //前n个元素的总计
    *++__result = __value;                        //指定给目的端
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
partial_sum(_InputIterator __first, _InputIterator __last,
            _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __partial_sum(__first, __last, __result, __VALUE_TYPE(__first), 
                       __binary_op);
}

template <class _InputIterator, class _OutputIterator, class _Tp>
_OutputIterator 
__adjacent_difference(_InputIterator __first, _InputIterator __last,
                      _OutputIterator __result, _Tp*)
{
  _Tp __value = *__first;                   //先记录第一个元素
  while (++__first != __last) {             //走过整个区间，
    _Tp __tmp = *__first;
    *++__result = __tmp - __value;
    __value = __tmp;
  }
  return ++__result;
}

template <class _InputIterator, class _OutputIterator>
_OutputIterator
adjacent_difference(_InputIterator __first,
                    _InputIterator __last, _OutputIterator __result)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first));
}

template <class _InputIterator, class _OutputIterator, class _Tp, 
          class _BinaryOperation>
_OutputIterator
__adjacent_difference(_InputIterator __first, _InputIterator __last, 
                      _OutputIterator __result, _Tp*,
                      _BinaryOperation __binary_op) {
  _Tp __value = *__first;
  while (++__first != __last) {
    _Tp __tmp = *__first;
    *++__result = __binary_op(__tmp, __value);        //将相邻的两个元素的运算结果，赋值给目的端
    __value = __tmp;
  }
  return ++__result;
}
// adjacent_difference用来计算[first, last)中相邻元素的差额
template <class _InputIterator, class _OutputIterator, class _BinaryOperation>
_OutputIterator 
adjacent_difference(_InputIterator __first, _InputIterator __last,
                    _OutputIterator __result, _BinaryOperation __binary_op)
{
  __STL_REQUIRES(_InputIterator, _InputIterator);
  __STL_REQUIRES(_OutputIterator, _OutputIterator);
  if (__first == __last) return __result;
  *__result = *__first;
  return __adjacent_difference(__first, __last, __result,
                               __VALUE_TYPE(__first),
                               __binary_op);
}

// Returns __x ** __n, where __n >= 0.  _Note that "multiplication"
// is required to be associative, but not necessarily commutative.
// 如果指定乘法运算，当n>=0时返回x^n
// _MonoidOperation必须满足结合律， 但不必满足交换律 
template <class _Tp, class _Integer, class _MonoidOperation>
_Tp __power(_Tp __x, _Integer __n, _MonoidOperation __opr)
{
  if (__n == 0)
    return identity_element(__opr);
  else {
    while ((__n & 1) == 0) {
      __n >>= 1;
      __x = __opr(__x, __x);               //取出证同元素identity_element
    }

    _Tp __result = __x;
    __n >>= 1;
    while (__n != 0) {
      __x = __opr(__x, __x);
      if ((__n & 1) != 0)
        __result = __opr(__result, __x);
      __n >>= 1;
    }
    return __result;
  }
}

template <class _Tp, class _Integer>
inline _Tp __power(_Tp __x, _Integer __n)
{
  return __power(__x, __n, multiplies<_Tp>());      //指定运算型式的乘法
}

// Alias for the internal name __power.  Note that power is an extension,
// not part of the C++ standard.

template <class _Tp, class _Integer, class _MonoidOperation>
inline _Tp power(_Tp __x, _Integer __n, _MonoidOperation __opr)
{
  return __power(__x, __n, __opr);
}

template <class _Tp, class _Integer>
inline _Tp power(_Tp __x, _Integer __n)
{
  return __power(__x, __n);
}

// iota is not part of the C++ standard.  It is an extension.
// iota算法由SGI专属，并不在STL标准之列，它用来设定某个区间的内容，使其内的每一个元素从指定的value值开始
// 呈现递增状态
template <class _ForwardIter, class _Tp>
void    //函数意义是: 在[first, last)区间内填入value, value+1, value+2
iota(_ForwardIter __first, _ForwardIter __last, _Tp __value)
{
  __STL_REQUIRES(_ForwardIter, _Mutable_ForwardIterator);
  __STL_CONVERTIBLE(_Tp, typename iterator_traits<_ForwardIter>::value_type);
  while (__first != __last)
    *__first++ = __value++;
}

__STL_END_NAMESPACE

#endif /* __SGI_STL_INTERNAL_NUMERIC_H */

// Local Variables:
// mode:C++
// End:
