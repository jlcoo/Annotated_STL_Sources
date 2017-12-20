//file:  lconfig11.cpp
//template in template memeber
//test _STL_LIMITED_DEFAULT_TEMPLATES in <stl_config.h>
//c++ primer p816

#include <iostream>
#include <cstddef>
using namespace std;

class alloc{};

template <class T, class Alloc=alloc, size_t BufSiz = 0>
class deque{
 public:
	deque(){cout<<"deque()"<<endl;}

};

template <class T, class Sequence = deque<T> >
class stack{
 public:
	stack(){cout<<"stack()"<endl;}
 private:
	Sequence c;
};

int main()
{
	stack<int> x;
}
