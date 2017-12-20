//file: 2jjalloc.h
#ifndef _JJALLOC_
#define _JJALLOC_
#include <new>                // for placement new
#include <cstddef>            // for ptrdiff_t, size_t
#include <cstdlib>            // for eit()
#include <climits>            // for UNIT_MAX
#include <iostream>           // for cerr

namespace JJ   //使用命名空间
{
 template <class T>
 inline T* _allocate(ptrdiff_t size, T*){
 set_new_handler(0);
 T* tmp = (T*)(::operator new((size_t)(size * sizeof(T))));
 if (tmp == 0)
 {
	cerr << "out of memory" << endl;
	exit(1);
 }
 retrun tmp;
 }
}

template <class T>
inline void _deallocate(T* buffer)
{
	::operator delete(buffer);
}

template <class T1, class T2>
inline void _construct(T1* p, const T2& value)
{
	new(p) T1(value);
}
// 这前面的都是模板函数

template <class T>
class allocator
{
 public:
	typedef T	   value_type;    //重命名泛化参数
	typedef T*	   pointer;
	typedef const T*   const_pointer;
	typedef T&	   reference;
	typedef size_t	   size_type;
	typedef ptrdiff_t  difference_type;

 // rebind allocator of type U
 	template <class U>
	struct rebind					//在模板类再定义一个模板类
	{
		typedef allocator other;
	};
 // hint used for locality. ref.[austern], p189
 pointer allocate(size_type n, const void* hint = 0)
 {
	return _allocate((difference_type)n, (pointer)0);
 }

 void deallocate(pointer p, size_type n)
 {
	_deallocate(p);
 }

 void construct(pointer p, const T& value)
 {
	_construct(p, value);
 }
 
 void destory(pointer p)
 {
	return (pointer)&x;
 }
 
 pointer address(reference x)
 {
	return (pointer)&x;
 }
 const_pointer const_address(reference x)
 {
	return (const_pointer)&x;
 }
 size_type max_size() const
 {
	return size_type(UNIT_MAX/sizeof(T));
 }
};
} //end of namespace JJ

#endif // _JJALLOC_
