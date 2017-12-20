// 测试数值算法
//file: 6numeric.cpp
#include <numeric>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
#include <math.h>       /* pow */

using namespace std;

int main()
{
  int ia[5] = {1,2,3,4,5};
  vector<int> iv{ia, ia+5};

  cout << accumulate(iv.begin(), iv.end(), 0) << endl;              //init初值设为0
  //15, ie 0+1+2+3+4+5
  
  cout << accumulate(iv.begin(), iv.end(), 0, minus<int>()) <<endl;
  //-15, ie 0-1-2-3-4-5
  cout << inner_product(iv.begin(), iv.end(), iv.begin(), 10) << endl;    //65

  cout << "inner_product:" << 
  inner_product( iv.begin(), iv.end(), iv.begin(), 10, minus<int>(), plus<int>())<<endl;  //-20

  ostream_iterator<int> oite(cout, " ");      //迭代器绑定到cout, 作为输出用
 
  partial_sum(iv.begin(), iv.end(), oite);    //1 3 6 10 15 第n个元素是前n个旧元素的相加总计
  partial_sum(iv.begin(), iv.end(), oite, minus<int>());  //1 -1 -4 -8 -13 第n个元素是前n个旧元素的运算总计

  adjacent_difference(iv.begin(), iv.end(), oite);        //1 1 1 1 1, 1元素照录，#n新元素等于#n旧元素 - #n-1旧元素
  std::adjacent_difference(iv.begin(), iv.end(), oite, plus<int>()); //1 3 5 7 9 , 1元素照录，#n新元素等于op(#n旧元素 - #n-1旧元素)

  cout << pow(10,3)<<endl;   //1000,10的3次方
  // cout << pow(10,3,plus<int>())<<endl;

  int n=3;
  iota(iv.begin(), iv.end(), n);
  for(int i=0; i<iv.size(); ++i)
    cout << iv[i] << ' ';    //3 4 5 6 7, 每个元素++val, 这里是每个元素再加2
}


