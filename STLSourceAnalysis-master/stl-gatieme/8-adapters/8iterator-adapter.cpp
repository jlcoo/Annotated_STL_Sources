#include <iterator>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;

int main(){
  // 将outite绑定到cout. 每次对outite指派一个元素，然后接一个" "。
  ostream_iterator<int> outite(cout, " ");
  int ia[]=  {0, 1, 2, 3, 4, 5};
  deque<int> id(ia, ia + 6);
  // 将所有元素拷贝到outite(那么也就是拷贝到cout)
  copy(id.begin(), id.end(), outite);                                 //0 1 2 3 4 5 
  cout<<endl;
  // 将ia[]的部分元素拷贝到id内. 使用front_insert_iterator.
  // 注意, front_insert_iterqtor会将assign操作改为push_front操作
  // vector不支持push_front()，这就是本例不用vector为示范对象的原因
  copy(ia + 1, ia + 2, front_inserter(id));
  copy(id.begin(), id.end(), outite);                                 //1 0 1 2 3 4 5
  cout<<endl;
  // 将ia[]的部分元素拷贝到id内. 使用back_insert_inserter.
  copy(ia + 3, ia + 5, back_inserter(id));
  copy(id.begin(), id.end(), outite);                                 //1 0 1 2 3 4 5 3 4 
  cout<<endl;
  // 搜索元素5所在的位置
  deque<int>::iterator ite = find(id.begin(), id.end(), 5);
  // 将ia[]的部分元素拷贝到id内. 使用insert_iterator
  copy(ia + 0, ia + 3, inserter(id, ite));                            //在5之前插入0 1 2
  copy(id.begin(), id.end(), outite);                                 //1 0 1 2 3 4 0 1 2 5 3 4  
  cout<<endl;
  // 以下, 将inite绑定到cin。将元素拷贝到inite，直到eos出现
  istream_iterator<int> inite(cin), eos;                              //eos: end-of-stream
  copy(inite, eos, inserter(id, id.begin()));
  copy(id.begin(), id.end(), outite);

  return 0;
}
