//file:lconfig6.cpp
//test _stl_function_TMPL_PARTIAL_ORDER in <stl_config.h>
//vc6[x] cb4 gcc[o]

#include <iostream>
using namespace std;

class alloc
{};

template <class T, class Alloc=alloc>
class vector{
 public:
  void swap(vector<T, Alloc>&){ cout<<"swap()"<<endl;}
};

#ifdef _STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>&y)
{
	x.swap(y);
}
#endif

int mian()
{
	vector<int> x,y;
	swap(x, y);
}
