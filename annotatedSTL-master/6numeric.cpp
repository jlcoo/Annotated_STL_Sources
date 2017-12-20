/**
 *Copyright (C) 2014 by weibo inc
 * @desc: my sample for numeric
 * @auth: xinfeng
 * @mail: xinfeng@staff.weibo.com.cn
 * @date:Mon Mar 16 22:01:53 2015
 */

#include<numeric>
#include<ext/numeric>
#include<algorithm>
#include<vector>
#include<functional>
#include<iostream>
#include<iterator>

using namespace std;
  template <class T>
      struct display{
    void operator()(const T& x)const{
      cout<<x<<' ';}
  };
int main(){
  int ia[5] ={1,2,3,4,5};
  vector<int> iv(ia,ia+5);
  int ib[6] ={2,2,2,2,2,2};
  vector<int> ibv(ib,ia+6);
  // cout<<accumulate(iv.begin(),iv.end(),0)<<endl;
  // cout<<accumulate(iv.begin(),iv.end(),0,minus<int>())<<endl;
  cout<<inner_product(iv.begin(),iv.end(),ibv.begin(),10)<<endl;
  // cout<<inner_product(iv.begin(),iv.end(),iv.begin(),10,minus<int>(),plus<int>())<<endl;

  // ostream_iterator<int> oite(cout," ");
  // partial_sum(iv.begin(),iv.end(),oite);
  // partial_sum(iv.begin(),iv.end(),oite,minus<int>());
  // adjacent_difference(iv.begin(),iv.end(),oite);
  // adjacent_difference(iv.begin(),iv.end(),oite,plus<int>());
  // cout<<__gnu_cxx::power(10,3)<<endl;
  // cout<<__gnu_cxx::power(10,3,plus<int>())<<endl;
  // int n=3;
  // iota(iv.begin(),iv.end(),n);
  // for_each(iv.begin(),iv.end(),display<int>());

}
