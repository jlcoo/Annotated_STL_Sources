#include <iostream>

template < typename T, T INVALID_VAL, int N > struct common_stuff
{
    static inline void foo() {}
    // whatever
};

template < typename T, T INVALID_VAL, int N > struct A : common_stuff<T,INVALID_VAL,N>
{
    using common_stuff<T,INVALID_VAL,N>::foo ;
    static inline bool dummy( T value )
    { std::cout << "generalization\n" ; foo() ; return value == INVALID_VAL ; }
};

template < void* INVALID_VAL, int N >
struct A<void*,INVALID_VAL,N> : common_stuff<void*,INVALID_VAL,N>
{
    using common_stuff<void*,INVALID_VAL,N>::foo ;
    static inline bool dummy( void* value )
    { std::cout << "specialization for void*\n" ; foo() ; return value != INVALID_VAL ; }
};

int main()
{
    A< int, -1, 100 >::dummy(50) ; // generalization
    A< void*, nullptr, 50 >::dummy(std::cout) ; // specialization for void*
}