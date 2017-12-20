// 测试关系运算仿函数
#include <iostream>
#include <functional>
using namespace std;

int main(int argc, char const *argv[])
{
  // 以下产生一些仿函数实体(对象)
  equal_to<int> equal_to_obj;
  not_equal_to<int> not_equal_to_obj;
  greater<int> greater_obj;
  greater_equal<int> greater_equal_obj;
  less<int> less_obj;
  less_equal<int> less_equal_obj;
  // 以下运用函数对象，履行函数功能
  cout << equal_to_obj(3, 5) << endl;                         //0
  cout << not_equal_to_obj(3, 5) << endl;                     //1
  cout << greater_obj(3, 5) << endl;                          //0
  cout << greater_equal_obj(3, 5) << endl;                    //0
  cout << less_obj(3, 5) << endl;                             //1
  cout << less_equal_obj(3, 5) << endl;                       //1
  // 以下直接以仿函数的临时对象履行函数功能
  cout << equal_to<int>()(3, 5) << endl;                      //0
  cout << not_equal_to<int>()(3, 5) << endl;                  //1
  cout << greater<int>()(3, 5) << endl;                       //0
  cout << greater_equal<int>()(3, 5) << endl;                 //0
  cout << less<int>()(3, 5) << endl;                          //1
  cout << less_equal<int>()(3, 5) << endl;                    //1

  return 0;
}

