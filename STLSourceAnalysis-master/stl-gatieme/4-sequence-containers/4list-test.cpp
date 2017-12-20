// 测试list
#include <list>
#include <iostream>
#include <algorithm>
using namespace std;


int main(int argc, char const *argv[])
{
  list<int> ilist;
  cout << "size=" << ilist.size() << endl;    //size=0

  ilist.push_back(0);
  ilist.push_back(1);
  ilist.push_back(2);
  ilist.push_back(3);
  ilist.push_back(4);
  cout << "size=" << ilist.size() << endl;    //size=5

  list<int>::iterator ite;
  for(ite = ilist.begin(); ite != ilist.end(); ++ite)
    cout << *ite << ' ';                      //0 1 2 3 4
  cout << endl;

  ite = find(ilist.begin(), ilist.end(), 3);
  if(ite != ilist.end())
    ilist.insert(ite, 99);

  cout << "size=" << ilist.size() << endl;    //size=6
  cout << *ite << endl;                       //3
  for(ite = ilist.begin(); ite != ilist.end(); ++ite)
    cout << *ite << ' ';                      //0 1 2 99 3 4
  cout << endl;

  ite = find(ilist.begin(), ilist.end(), 1);
  if (ite != ilist.end())
    cout << *(ilist.erase(ite)) << endl;      //2

  for(ite = ilist.begin(); ite != ilist.end(); ++ite)
    cout << *ite << ' ';                      //0 2 99 3 4 
  cout << endl;

  int ivt[5] = {5, 6, 7, 8 , 9};
  list<int> ilist2(ivt, ivt + 5);
  for (auto &x : ilist2)
    cout << x << ' ';   //5 6 7 8 9
  cout << endl;

  ite = find(ilist.begin(), ilist.end(), 99);
  ilist.splice(ite, ilist2);
  for (auto &x : ilist)
    cout << x << ' ';   //0 2 5 6 7 8 9 99 3 4 合并在ite之前
  cout << endl;

  ilist.reverse();
  for (auto &x : ilist)
    cout << x << ' ';  //4 3 99 9 8 7 6 5 2 0
  cout << endl;

  ilist.sort();
  for (auto &x : ilist)  
    cout << x << ' ';  //0 2 3 4 5 6 7 8 9 99
  cout << endl;

  cout << "list2: ";
  for (auto &x : ilist2)
    cout << x << ' ';   //5 6 7 8 9
  cout << endl;

  return 0;
}

