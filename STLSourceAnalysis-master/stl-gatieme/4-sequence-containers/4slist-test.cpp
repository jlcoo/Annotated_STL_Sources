// 测试当链表slist
// #include <slist>
#include <forward_list>
#include <iostream>
#include <algorithm>
using namespace std;

int main(int argc, char const *argv[])
{
  forward_list<int> islist;
  cout << "empty = " << islist.empty() << endl;    //empty = 1是空
  islist.push_front(9);
  islist.push_front(1);
  islist.push_front(2);
  islist.push_front(3);
  islist.push_front(4);
  cout << "empty = " << islist.empty() << endl;    //empty = 0 非空      
  forward_list<int>::iterator ite = islist.begin();
  forward_list<int>::iterator ite2 = islist.end();

  for(; ite != ite2; ++ite)
    cout << *ite << ' ';            //4 3 2 1 9 ，最后插入的元素在最前面
  cout << endl;

  ite = find(islist.begin(), islist.end(), 1);  //找到值为1的位置
  if (ite != islist.end())
    islist.insert_after(ite, 99);       //在ite迭代器所指位置的后面插入99

  cout << "empty = " << islist.empty() << endl;   //empty = 0 非空
  cout << *ite << endl;                 //ite指向元素1

  ite = islist.begin();
  ite2 = islist.end();
  for(; ite != ite2; ++ite)
    cout << *ite << ' ';                //4 3 2 1 99 9 插入99后的单链表
  cout << endl;

  ite = find(islist.begin(), islist.end(), 3);  //找到值为3的位置
  if (ite != islist.end())
    cout << *(islist.erase_after(ite)) << endl; //移除ite所指位置后面一个元素2,这个位置就变成了1

  ite = islist.begin();
  ite2 = islist.end();
  for(; ite != ite2; ++ite)
    cout << *ite << ' ';                        //4 3 1 99 9 
  cout << endl;

  return 0;
}

