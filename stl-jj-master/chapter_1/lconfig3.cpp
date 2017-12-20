//file : lconfig3.cpp
//测试在 clas template 中拥有 static data members。
//test _STL_STATIC_TEMPLATE_MEMBER_BUG, DEFIEN IN <stl_config.h>
//ref. c++ primer 3/e, p.839
//vc6[0] cb4[x] gcc[o]
//cb4 does not support static data member initialization.
//
#include <iostream>
using namespace std;

template <typename T> class testClass{
public:  //测试方便使用public
 static int _data;
};

// 为static data member 进行定义 配置内存 ， 并初始化
//testClass<int>::_data=1;
//testClass<char>::_data=2;

int main()
{
 cout<<testClass<int>::_data<<endl;
 cout<<testClass<char>::_data<<endl;
 testClass<int> obji1, obji2;
 testClass<char> objc1, objc2;

 cout<<obji1._data<<endl;
 cout<<obji2._data<<endl;
 cout<<objc1._data<<endl;
 cout<<objc2._data<<endl;

 obji1._data = 3;
 objc2._data = 4;
 
 cout<<obji1._data<<endl;
 cout<<obji2._data<<endl;
 cout<<objc1._data<<endl;
 cout<<objc2._data<<endl;
}
