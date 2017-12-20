// 测试基本算法
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <string>
using namespace std;
template <class T>
struct display{
  void operator()(const T& x)const{
    cout << x << ' ';
  }
};

int main(){
  int ia[10]={0,1,2,3,4,5,6,7,8,9};
  vector<int> iv1(ia, ia+5);
  vector<int> iv2(ia, ia+9);
  // 判断两个区间的第一个不匹配点，返回一个由两迭代器组成的pair
  // 其中第一个迭代器指向第一区间的不匹配点，第二个迭代器指向第二个区间的不匹配点
  cout<< *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).first) << endl;  //0 应该先判断迭代器是否不等于容器的end()，然后才可以做输出操作
  cout<< *(mismatch(iv1.begin(), iv1.end(), iv2.begin()).second) << endl; //5
  // 如果两个序列在[first, last)区间内相等，equal()返回true
  // 如果第二个系列的元素比较多，多出来的元素不予考虑
  cout<< equal(iv1.begin(), iv1.end(), iv2.begin()) << endl;              //1   true
  cout<< equal(iv1.begin(), iv1.end(), &ia[3], less<int>()) << endl;      //1   true
  cout<< equal(iv1.begin(), iv1.end(), &ia[3]) << endl;                   //0   false

  fill(iv1.begin(), iv1.end(), 9);                                        //区间内的所有元素全部填9
  fill_n(iv1.begin(), 3, 7);                                              //从迭代器开始的位置开始，填3个7
  for_each(iv1.begin(), iv1.end(), display<int>());                       //7 7 7 9 9
  cout << endl;

  vector<int>::iterator ite1 = iv1.begin();                               //指向7
  vector<int>::iterator ite2 = ite1;
  advance(ite2, 3);                                                       //指向9 
  for_each(ite2, iv1.end(), display<int>());                              //9 9
  cout << endl;

  iter_swap(ite1, ite2);                                                  //两个迭代器所指元素对调
  cout << *ite1 << ' ' << *ite2 << endl;                                  //9 7
  for_each(iv1.begin(), iv1.end(), display<int>());                       //9 7 7 7 9  
  cout << endl;

  // 取两值较大者
  cout << max(*ite1, *ite2) << endl;                                      //9
  // 取两值较小者
  cout << min(*ite1, *ite2) << endl;                                      //7
  // 此刻状态，iv1: 9 7 7 7 9 ; iv2: 0 1 2 3 4 5 6 7 8 
  for_each(iv1.begin(), iv1.end(), display<int>());                       //9 7 7 7 9 
  cout << endl;
  for_each(iv2.begin(), iv2.end(), display<int>());                       //0 1 2 3 4 5 6 7 8
  cout << endl;
  swap(*iv1.begin(), *iv2.begin());
  for_each(iv1.begin(), iv1.end(), display<int>());                       //0 7 7 7 9 
  cout << endl;
  for_each(iv2.begin(), iv2.end(), display<int>());                       //9 1 2 3 4 5 6 7 8
  cout << endl;
  // 准备两个字符串数组
  string stral1[] = {"chen", "Xin", "feng"};
  string stral2 []= {"chen", "xin", "feng"};
  cout<< lexicographical_compare(stral1, stral1 + 2, stral2, stral2 + 2) << endl; //1 stral1小于stral2
  cout<< lexicographical_compare(stral1, stral1 + 2, stral2, stral2 + 2, greater<string>()) << endl; //0 stral1不大于stral2

}
