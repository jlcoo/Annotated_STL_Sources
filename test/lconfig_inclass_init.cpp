#include <iostream>
// 静态常量整数成员在class内部直接初始化
using namespace std;

template <typename T>
class testClass {
public:       //expedient
  static const int _datai = 5;
  static const long _datal = 3L;
  static const char _datac = 'C';
};


int main(int argc, char const *argv[])
{
  cout << testClass<int>::_datai << endl;       //会输出5
  cout << testClass<int>::_datal << endl;       //会输出3
  cout << testClass<int>::_datac << endl;       //会输出C
  
  return 0;
}
