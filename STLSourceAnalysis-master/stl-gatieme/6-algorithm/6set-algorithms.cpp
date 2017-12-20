// 测试set相关算法
#include <set>            //multiset
#include <iostream>
#include <algorithm>
#include <iterator>       //ostream_iterator
using namespace std;

template <class T>
struct display{
  void operator()(const T& x){
    cout<< x << ' ';
}

};


int main(){
  int ia1[6] = {1, 3, 5, 7, 9, 11};
  int ia2[7] = {1, 1, 2, 3, 5, 8, 13};

  multiset<int> S1(ia1, ia1 + 6);
  multiset<int> S2(ia2, ia2 + 7);
  for_each(S1.begin(), S1.end(), display<int>());  //1 3 5 7 9 11
  cout << endl;
  for_each(S2.begin(), S2.end(), display<int>());  //1 1 2 3 5 8 13
  cout << endl;

  multiset<int>::iterator  first1 = S1.begin();
  multiset<int>::iterator  last1 = S1.end();
  multiset<int>::iterator  first2 = S2.begin();
  multiset<int>::iterator  last2 = S2.end();

  cout << "Union of S1 and S2: ";
  set_union(first1, last1, first2, last2, 
            ostream_iterator<int>(cout, " "));    //并集: 1 1 2 3 5 7 8 9 11 13 
  cout << endl;

  first1 = S1.begin();                            //保险起见
  first2 = S2.begin();
  cout << "Intersection of S1 and S2: ";
  set_intersection(first1, last1, first2, last2,
                   ostream_iterator<int>(cout, " ")); //交集：1 3 5
  cout << endl;
  
  cout << "Difference of S1 and S2: ";
  first1 = S1.begin();                            //保险起见
  first2 = S2.begin();
  set_difference(first1, last1, first2, last2,
                 ostream_iterator<int>(cout, " "));   //差集: 7 9 11 
  cout << endl;

  cout << "Difference of S1(S2 - S1) and S2: ";
  first1 = S1.begin();                            //保险起见
  first2 = S2.begin();
  set_difference(first2, last2, first1, last1,      //对称差集既是交集的补集
                 ostream_iterator<int>(cout, " ")); //对称差集: 1 2 8 13 (交换了两个set的顺序) 
  cout << endl;

  cout << "Symmetric difference of S1 and S2: ";
  first1 = S1.begin();                            //保险起见
  first2 = S2.begin();
  set_symmetric_difference(first1, last1, first2, last2,
                           ostream_iterator<int>(cout, " ")); //对称差集: 1 2 7 8 9 11 13  
  cout << endl;

  first1 = S2.begin();
  first2 = S1.begin();
  last1 = S2.end();
  last2 = S1.end();
  cout << "Difference of S1(S2 - S1) and S2: ";
  set_difference(first1, last1, first2, last2,
                 ostream_iterator<int>(cout, " ")); //1 2 8 13 
  cout << endl;
  
  return 0;
}
