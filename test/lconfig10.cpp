#include <iostream>
#include <cstddef>     //for size_t
using namespace std;
class alloc {
};
// 测试template参数是否根据前一个template参数而设定默认参数
template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
  deque() { cout << "deque" << endl; }
};
// 根据前一个参数值T，设定下一个参数Sequence的默认值为deque<T>
template <class T, class Sequence = deque<T> >
class stack {
public:
  stack() { cout << "Stack" << endl; }
private:
  Sequence c;
}; 

int main(int argc, char const *argv[])
{
  stack<int> x;   //输出为  deque; Stack, 证明调用了默认参数
  
  return 0;
}
