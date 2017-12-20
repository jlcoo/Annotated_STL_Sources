#include <iostream>
using namespace std;

// 重载operator(), 变成仿函数
template <typename T>
struct pluso {
  T operator() (const T& x, const T& y) const 
  { return x + y; }
};

template <class T>
struct minuso {
  T operator() (const T& x, const T& y) const 
  { return x - y; }
};

int main(int argc, char const *argv[])
{
  // 以下产生仿函数对象
  pluso<int> plusobj;
  minus<int> minusobj;

  // 以下使用仿函数，就像一般函数一样
  cout << plusobj(3, 5) << endl;          //输出8
  cout << minusobj(3, 5) << endl;         //输出-2

  // 以下直接产生仿函数的临时对象(第一对小括号)，并调用（第二对小括号）
  cout << plus<int>() (43, 50) << endl;   //输出93
  cout << minus<int>() (43, 50) << endl;  //输出-7

  return 0;
}

