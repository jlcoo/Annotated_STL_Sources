#include <iostream>
// 为了测试 class template explicit specialization

using namespace std;
#define __STL_TEMPLATE_NULL   template<>    /*blank*/  //blank gcc 都编译不过，template<> 却可以

template <class key>
struct hash {
  void operator()() { cout << "hash<T>" <<endl; }
};
// explicit specialization (explicit 实例化)
__STL_TEMPLATE_NULL struct hash<char> {
  void operator()() { cout << "hash<char>" << endl; }
}; 

__STL_TEMPLATE_NULL struct hash<unsigned char> {
  void operator()() { cout << "hash<unsigned char>" << endl; }
}; 

int main(int argc, char const *argv[])
{
  hash<long> t1;
  hash<char> t2;
  hash<unsigned char> t3;

  t1();
  t2();
  t3();
//输出: hash<T>
// hash<char>
// hash<unsigned char>

  return 0;
}
