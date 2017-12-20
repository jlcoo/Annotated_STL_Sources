/**
 *Copyright (C) 2015 by weibo inc
 * @desc: make_heap sample
 * @auth: xinfeng
 * @mail: xinfeng@staff.weibo.com.cn
 * @date:Fri Mar 20 09:55:36 2015
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;



template <class T>
struct display
{
  void operator()(const T& x){
    cout<<x<<endl;
  }
};
int main(int argc, char *argv[])
{
  int ia[9]={0,1,2,3,4,8,9,3,5};
  vector<int> ivec(ia,ia+9);
  make_heap(ivec.begin(),ivec.end());
  ivec.push_back(7);
  //for_each(ivec.begin(),ivec.end(),display<int>());
  push_heap(ivec.begin(),ivec.end());
  for_each(ivec.begin(),ivec.end(),display<int>());
  pop_heap(ivec.begin(),ivec.end());
  cout<<ivec.back()<<endl;
  return 0;

}
