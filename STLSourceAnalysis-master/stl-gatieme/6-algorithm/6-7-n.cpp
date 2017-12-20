// 测试工作原理比较复杂的其他算法
// 有些编译器不接受random_shuffle()
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>                   //这个头文件定义了ostream_iterator
using namespace std;

struct even                           //这是一个仿函数
{
  bool operator()(int x) const
  { return x % 2 ? false : true; }
};

int main(int argc, char *argv[])
{
  int ia[] = { 12, 17, 20, 22, 23, 30, 33, 40 };
  vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));

  cout << *lower_bound(iv.begin(), iv.end(), 21) << endl;         //22
  cout << *upper_bound(iv.begin(), iv.end(), 21) << endl;         //22
  cout << *lower_bound(iv.begin(), iv.end(), 22) << endl;         //22
  cout << *upper_bound(iv.begin(), iv.end(), 22) << endl;         //23
  // 面对有序区间(sorted range)，可以二分查找 寻找某个元素
  cout << binary_search(iv.begin(), iv.end(), 33) << endl;        //1 (true)
  cout << binary_search(iv.begin(), iv.end(), 34) << endl;        //0 (false)
  // 下一个排列组合
  next_permutation(iv.begin(), iv.end());
  // ostream_iterator<int> os(cout);
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //12 17 20 22 23 30 40 33 
  cout << endl;
  // 上一个排列组合
  prev_permutation(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //12 17 20 22 23 30 33 40 
  cout << endl;
  // 随机重排
  random_shuffle(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //23 17 33 20 12 30 40 22 
  cout << endl;
  // 将iv.begin()+4 - iv.begin()个元素排序，放进
  // [iv.begin(), iv.begin()+4]区间内; 剩余元素不保证维持原相对次序
  partial_sort(iv.begin(), iv.begin() + 4, iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //12 17 20 22 33 30 40 23  
  cout << endl;
  // 排序(缺省为递增排序)
  sort(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //12 17 20 22 23 30 33 40 
  cout << endl;
  // 排序(指定递减排序)
  sort(iv.begin(), iv.end(), greater<int>());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //40 33 30 23 22 20 17 12  
  cout << endl;
  // 在iv尾端附加新元素
  iv.push_back(22);
  iv.push_back(30);
  iv.push_back(17);
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //40 33 30 23 22 20 17 12 22 30 17 
  cout << endl;
  // 排序,并保持相对位置
  stable_sort(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //12 17 17 20 22 22 23 30 30 33 40 
  cout << endl;
  // 面对一个有序区间，找出其中一个子区间，其内每个元素都与特定的元素相同，返回该子区间的头尾迭代器
  // 如果没有这样的子区间，返回的头尾迭代器均指向该特定元素可插入(并仍保持排序)的地点
  pair<vector<int>::iterator, vector<int>::iterator> pairIte;
  pairIte = equal_range(iv.begin(), iv.end(), 22);
  cout << *(pairIte.first) << endl;                               //22 (lower_bound)
  cout << *(pairIte.second) << endl;                              //23 (upper_bound)

  pairIte = equal_range(iv.begin(), iv.end(), 25);
  cout << *(pairIte.first) << endl;                               //30 (lower_bound)
  cout << *(pairIte.second) << endl;                              //30 (upper_bound)
  // 随机重排
  random_shuffle(iv.begin(), iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //22 33 12 40 20 22 23 30 17 17 30  
  cout << endl;
  // 将小于*(iv.begin() + 5)(本例为22)的元素置于该元素的左
  // 其余置于该元素的右，不保证维持原有的相对位置
  nth_element(iv.begin(), iv.begin() + 5, iv.end());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //22 17 12 17 20 22 23 30 40 33 30
  cout << endl;
  // 将大于*(iv.begin() + 5)(本例为22)的元素置于该元素的左
  // 其余置于该元素的右，不保证维持原有的相对位置
  nth_element(iv.begin(), iv.begin() + 5, iv.end(), greater<int>());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //23 30 33 40 30 22 22 20 17 12 17 
  cout << endl;
  // 以是否符合even()条件为依据，将符合者置于左段，不符合者置于右段
  // 保证维持原有的相对位置，如不需要维持原有的相对位置，可改用partition()
  stable_partition(iv.begin(), iv.end(), even());
  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));   //30 40 30 22 22 20 12 23 33 17 17 
  cout << endl;

  return 0;
}


