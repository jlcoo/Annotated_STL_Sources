// 测试逻辑仿函数
#include <iostream>
#include <functional>
using namespace std;

int main(int argc, char const *argv[])
{
  // 以下产生一些仿函数实体(对象)
  logical_and<int> and_obj;
  logical_or<int> or_obj;
  logical_not<int> not_obj;
  // 以下运用函数对象，履行函数功能
  cout << and_obj(true, true) << endl;                    //1
  cout << or_obj(true, false) << endl;                    //1
  cout << not_obj(true) << endl;                          //0
  // 以下直接以仿函数的临时对象履行函数功能
  cout << logical_and<int>()(true, true) << endl;         //1
  cout << logical_or<int>()(true, false) << endl;         //1
  cout << logical_not<int>()(true) << endl;               //0

  return 0;
}