// Copyright (C) 2015 by weibo inc
/**
 * @author:xinfeng
 */
#include <iostream>
#include <algorithm>
#include <deque>
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

  // {
  //   int ia[]={0,1,2,3,4,5,6,7,8};
  //   copy(ia+2,ia+7,ia);
  //   for_each(ia,ia+9,display<int>());
  // }

  // {
  //   int ia[]={0,1,2,3,4,5,6,7,8};
  //   copy(ia+2,ia+7,ia+4);
  //   for_each(ia,ia+9,display<int>());

  // }
  {
    int ia[]={0,1,2,3,4,5,6,7,8};
    deque<int> id(ia,ia+9);
    deque<int>::iterator first = id.begin();
    deque<int>::iterator last  =  id.end();
    advance(first,2);
    advance(last,-2);
    cout<<*first<<endl;
    cout<<*last<<endl;
    deque<int>::iterator result = id.begin();
    copy(first,last,result);
    for_each(id.begin()
             ,id.end(),display<int>());

  }

  return 0;
}
