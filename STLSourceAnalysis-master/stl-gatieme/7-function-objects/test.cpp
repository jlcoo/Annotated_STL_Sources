#include <functional>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
  greater<int> ig;
  // 启用流 str 中的 boolalpha 标志，如同通过调用 str.setf(std::ios_base::boolalpha)
  //  禁用流 str 中的 boolalpha 标志，如同通过调用 str.unsetf(std::ios_base::boolalpha)
  // std::boolalpha 是 I/O 操纵符，故可用如 out << std::boolalpha 的表达式对任何 std::basic_ostream 类型的 out ，
  // 或用如 in >> std::boolalpha 的表达式对任何 std::basic_istream 类型的 in 调用
  cout << boolalpha << ig(4, 6) << endl;      //false  boolalpha能直接输出false或者true
  cout << greater<int>() (6, 4) << endl;      //true

  return 0;
}
