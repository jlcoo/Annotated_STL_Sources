#include <iostream>
#include <cstddef>
// 类模板的某个具体实现与其友元函数模板的某个实现有一一对应的关系
using namespace std;


class alloc {
};
template <class T, class Alloc = alloc, size_t BufSiz = 0>
class deque {
public:
  deque() { cout << "deque" << ' '; }
};


template <class T, class Sequence = deque<T> >
class stack {
  template <class U, class Y>
  friend bool operator==(const stack<U, Y>&,
                        const stack<U, Y>& ) ;
  template <class U, class Y>
  friend bool operator<(const stack<U, Y>&,
                        const stack<U, Y>& ) ;
  // friend bool operator== <> (const stack&, const stack&);
  // friend bool operator< <> (const stack&, const stack&);

public:
  stack() { cout << "Stack" << endl; }
private:
  Sequence c;
}; 

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>& x,
                const stack<T, Sequence>& y) {
  return cout << "operator==" << '\t';
}
template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x,
                const stack<T, Sequence>& y) {
  return cout << "operator<" << '\t';
}


int main(int argc, char const *argv[])
{
  stack<int> x;
  stack<int> y;

  cout << (x == y) << endl;
  cout << (x < y) << endl;   
  // operator==  1  输出
  // operator< 1

  stack<char> y1;
  // cout << (x == y1) << endl;  //会报错
  // cout << (x < y1) << endl;
  
  return 0;
}

