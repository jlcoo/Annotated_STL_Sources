// 测试在 class template中拥有static data members
#include <iostream>
using namespace std;

template <typename T>
class testClass {
public:
  static int _data;
};
// 为static data members 进行定义（配置内存），并设定初值
template <>   //没有用到模板变量，<>里面必须为空的
int testClass<int>::_data   = 1;

template <>
int testClass<char>::_data  = 2;

int main(int argc, char const *argv[])
{
  // 以下CB4表现不佳，并没有接受初值设定
  cout << testClass<int>::_data   << endl;    //GCC, VC6：1   CB: 0
  cout << testClass<char>::_data  << endl;    //GCC, VC6：2   CB: 0

  testClass<int>  obji1, obji2;
  testClass<char> objc1, objc2;

  cout << obji1._data << endl;
  cout << obji2._data << endl;
  cout << objc1._data << endl;
  cout << objc2._data << endl;

  obji1._data = 3;
  objc2._data = 4;
  cout << obji1._data << endl;              // GCC, VC6:3 CB4:3   不同对象的static变量会同时改变
  cout << obji2._data << endl;              // GCC, VC6:3 CB4:3
  cout << objc1._data << endl;              // GCC, VC6:4 CB4:4 
  cout << objc2._data << endl;              // GCC, VC6:4 CB4:4

  return 0;
}

