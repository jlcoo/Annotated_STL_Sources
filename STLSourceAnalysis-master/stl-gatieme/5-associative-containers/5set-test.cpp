// 测试set，由于RB-tree接口没有公开，无法测试5rbtree-test.cpp
#include <set>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
  int ia[5] = {0, 1, 2, 3, 4};
  set<int> iset(ia, ia + 5);
  cout << "size = " << iset.size() << endl;         //size = 5
  cout << "3 count = " << iset.count(3) <<endl;     //3 count = 1
  iset.insert(3) ;
  cout << "size = " << iset.size() << endl;         //size = 5
  cout << "3 count = " << iset.count(3) <<endl;     //3 count = 1
  iset.insert(5);
  cout << "size = " << iset.size() << endl;         //size = 6
  cout << "5 count = " << iset.count(5) <<endl;     //5 count = 1

  iset.erase(1);
  cout << "size = " << iset.size() << endl;         //size = 5
  cout << "3 count = " << iset.count(3) <<endl;     //3 count = 1
  cout << "1 count = " << iset.count(1) <<endl;     //1 count = 0

  set<int>::iterator ite1 = iset.begin();
  set<int>::iterator ite2 = iset.end();
  for(; ite1 != ite2; ++ite1)
    cout << *ite1 << ' ';                           //0 2 3 4 5 
  cout << endl;
  // 使用STL算法find()来搜寻元素，可以有效运作，但不是好办法
  ite1 = find(iset.begin(), iset.end(), 3);
  if(ite1 != iset.end())
    cout << "3 found!" << endl;                     //3 found!
  ite1 = find(iset.begin(), iset.end(), 1);
  if(ite1 == iset.end())
    cout << "1 not found!" << endl;                 //1 not found!
  // 企图通过迭代器来改变set元素，是不被允许的
  *ite1 = 9;        //会报错！     const修饰过后只能读

  return 0;
}

