#include <iostream>
using namespace std;

#define _STL_TEMPLATE_NULL

template <class key> struct hash{
	cout<<"hash<char>"<<endl;
};

_STL_TEMPLATE_NULL struct hash<char>{
	void operator() () {cout<<"hash<unsigned char>"<<endl;}
};

_STL_TEMPLATE_NULL struct hash<unsigned char>{
	void operator()(){cout<<"hash<unsigned char>"<<endl;}
};

int  main()
{
	hash<long> t1;
	hash<char> t2;
	hash<unsigned char>t3;

	t1();
	t2();
	t3();
}
