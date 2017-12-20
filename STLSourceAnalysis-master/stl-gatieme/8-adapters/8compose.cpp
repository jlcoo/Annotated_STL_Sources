// 测试compose(function adapters(函数适配器))
// compose1是GCC独家的产品
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <iterator>
#include "compose11.hpp"
using namespace std;

int main(int argc, char const *argv[])
{
  // 将outite绑定到cout. 每次对outite指派一个元素，然后接一个" "
  ostream_iterator<int> outite(cout, " ");
  int ia[6] = {2, 21, 12, 7, 19, 23};
  vector<int> iv(ia, ia + 6);
  // 欲于每个元素v身上执行(v + 2)*3
  // 注意, for_each() 是nonmutating algorithm. 元素内容不能改
  // 所以，执行后iv的内容并不变
  for_each(iv.begin(), iv.end(), compose_f_gx(                    //compose1没有定义
                              bind2nd(multiplies<int>(), 3),
                              bind2nd(plus<int>(), 2) ));
  copy(iv.begin(), iv.end(), outite);                             //2 21 12 7 19 23 
  cout << endl;

  // 如果这样，输出另一地点(cout), 是可以的
  transform(iv.begin(), iv.end(), outite, compose_f_gx(           //compose1没有定义
                              bind2nd(multiplies<int>(), 3),      //12 69 42 27 63 75 
                              bind2nd(plus<int>(), 2) ));
  cout << endl;                                       

  return 0;
}
