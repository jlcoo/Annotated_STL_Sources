#include <iostream>
using namespace std;
// increment/dereference 操作符
class INT
{
  friend ostream& operator<<(ostream& os, const INT& i);
public:
  INT(int i) : m_i(i) { };

  // prefix : increment and then fetch
  INT& operator++ ()
  {
    ++(this->m_i);    //随着class的不同，改行应该有所不同的操作
    return *this;
  }

  // postfix : fetch and then increment
  const INT operator++ (int)
  {
    INT temp = *this;
    ++(*this);
    return temp;
  }

  // prefix : increment and then fetch
  INT& operator-- ()
  {
    --(this->m_i);    //随着class的不同，改行应该有所不同的操作
    return *this;
  }

  // postfix : fetch and then increment
  const INT operator-- (int)
  {
    INT temp = *this;
    --(*this);
    return temp;
  }

  // dereference
  int& operator* () const
  {
    return (int&) m_i;
    // 以上转换操作告诉编译器确实要将 const int 转换为non-const lvalue.
    // 如果没有这样明白的转换，有些编译器会给出警告，更有些严格的编译器会视为出错
  }
private:
  int m_i;
};

ostream& operator<< (ostream& os, const INT& i)
{
  os << '[' << i.m_i << ']';
  return os;
}

int main(int argc, char const *argv[])
{
  INT I(5);
  cout << I++;   //[5]  后置迭代不会在输出之前改变
  cout << ++I;   //[7]  前置会在输出之前改变
  cout << I--;   //[7]
  cout << --I;   //[5]
  cout << *I;    //5

  return 0;
}
