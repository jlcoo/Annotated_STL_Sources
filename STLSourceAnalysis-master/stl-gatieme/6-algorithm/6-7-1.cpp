// 单纯的数据处理，其他算法
#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

template <class T>
struct display{                     //这是一个仿函数，因为重载了函数操作符()
  void operator()(const T& x) const
  { cout << x << ' '; }
};

struct even                         //偶数
{                                   //这是一个仿函数
  bool operator()(int x) const
  { return x % 2 ? false : true; }
};
class even_by_two{
public:                             //这是一个仿函数
  int operator()() const
  { return _x += 2; }
private:
  static int _x;
};

int even_by_two::_x= 0;
int main(int argc, char *argv[])
{
  int ia[] = { 0, 1, 2, 3, 4, 5, 6, 6, 6, 7, 8 };
  vector<int> iv(ia, ia + sizeof(ia) / sizeof(int));
  // 找出iv中相邻元素值相等的第一个元素
  cout << *adjacent_find(iv.begin(), iv.end()) << endl;    //6
  // 找出iv中相邻元素值相等的第一个元素 
  cout << *adjacent_find(iv.begin(), iv.end(), equal_to<int>()) << endl; //6
  // 找出iv中元素值为6的元素个数
  cout << count(iv.begin(), iv.end(), 6) << endl;          //3
  // 找出iv中小于7的元素
  cout << count_if(iv.begin(), iv.end(), bind2nd(less<int>(), 7)) 
       << endl;                                            //9
  // 找出iv中元素为4的第一个元素的所在位置的值
  cout << *find(iv.begin(), iv.end(), 4) << endl;          //4
  // 找出iv中大于2的第一个元素的所在位置
  cout << *find_if(iv.begin(), iv.end(), bind2nd(greater<int>(), 2)) 
       << endl;                                            //3
  // 找出iv之中子序iv2所出现的最后一个位置(再往后3个位置的值)
  vector<int> iv2(ia + 6, ia + 8);                         //{6, 6}
  cout << *(find_end(iv.begin(), iv.end(), iv2.begin(), iv2.end())+ 3) 
       << endl;                                            //8
  // 找出iv之中子序iv2所出现的第一个位置(再往后3个位置的值)
  cout << *(find_first_of(iv.begin(), iv.end(), iv2.begin(), iv2.end())+ 3) 
       << endl;                                            //7     
  // 遍历整个iv区间,对每一个元素施行display操作(不得改变元素内容)
  for_each(iv.begin(), iv.end(), display<int>());          //0 1 2 3 4 5 6 6 6 7 8 
  cout << endl;
  // 遍历整iv2区间，对每个元素施行even_by_two操作(得改变元素值)
  generate(iv2.begin(), iv2.end(), even_by_two());
  for_each(iv2.begin(), iv2.end(), display<int>());        //2 4 
  cout << endl;
  // 迭代指定区间(起点和长度)，对每个元素施行even_by_two操作(得改变元素值)
  generate_n(iv.begin(), 3, even_by_two());
  for_each(iv.begin(), iv.end(), display<int>());          //6 8 10 3 4 5 6 6 6 7 8
  cout << endl;
  // 删除元素6
  remove(iv.begin(), iv.end(), 6);
  for_each(iv.begin(), iv.end(), display<int>());          //8 10 3 4 5 7 8 6 6 7 8 后面的表示残余
  cout << endl;
  // 删除元素6，结果置于另一个区间
  vector<int> iv3(12);
  remove_copy(iv.begin(), iv.end(), iv3.begin(), 6);
  for_each(iv3.begin(), iv3.end(), display<int>());        //8 10 3 4 5 7 8 7 8 0 0 0 后面的表示残余
  cout << endl;
  // 删除小于6的元素
  remove_if(iv.begin(), iv.end(), bind2nd(less<int>(), 6));
  for_each(iv.begin(), iv.end(), display<int>());          //8 10 7 8 6 6 7 8 6 7 8 后面的表示残余
  cout << endl;
  // 删除小于7的元素, 结果置于另一个区间
  remove_copy_if(iv.begin(), iv.end(), iv3.begin(), bind2nd(less<int>(), 7));
  for_each(iv3.begin(), iv3.end(), display<int>());        //8 10 7 8 7 8 7 8 8 0 0 0 后面的表示残余
  cout << endl;
  // 将所有元素6改为元素3
  replace(iv.begin(), iv.end(), 6, 3);
  for_each(iv.begin(), iv.end(), display<int>());          //8 10 7 8 3 3 7 8 3 7 8
  cout << endl;
  // 将所有元素3改为元素5，结果置于另一区间
  replace_copy(iv.begin(), iv.end(), iv3.begin(), 3, 5);
  for_each(iv3.begin(), iv3.end(), display<int>());        //8 10 7 8 5 5 7 8 5 7 8 0 
  cout << endl;
  // 将所有小于5的元素值，改为元素值2
  replace_if(iv.begin(), iv.end(), bind2nd(less<int>(), 5), 2);
  for_each(iv.begin(), iv.end(), display<int>());          //8 10 7 8 2 2 7 8 2 7 8 
  cout << endl;
  // 将所有等于8的元素，改为9，结果置于另一区间
  replace_copy_if(iv.begin(), iv.end(), iv3.begin(),
                  bind2nd(equal_to<int>(), 8), 9);
  for_each(iv3.begin(), iv3.end(), display<int>());        //9 10 7 9 2 2 7 9 2 7 9 0  
  cout << endl;
  // 逆向重排每个元素
  reverse(iv.begin(), iv.end());
  for_each(iv.begin(), iv.end(), display<int>());          //8 7 2 8 7 2 2 8 7 10 8
  cout << endl;
  // 逆向重排每个元素，结果置于另一个空间
  reverse_copy(iv.begin(), iv.end(), iv3.begin());
  for_each(iv3.begin(), iv3.end(), display<int>());        //8 10 7 8 2 2 7 8 2 7 8 0 
  cout << endl;
  // 旋转(互换元素) [first, middle)和[middle, last)
  rotate(iv.begin(), iv.begin() + 4, iv.end());
  for_each(iv.begin(), iv.end(), display<int>());          //7 2 2 8 7 10 8 8 7 2 8 
  cout << endl;
  // 旋转(互换元素) [first, middle)和[middle, last), 结果置于另一区间
  rotate_copy(iv.begin(), iv.begin() + 5, iv.end(), iv3.begin());
  for_each(iv3.begin(), iv3.end(), display<int>());        //10 8 8 7 2 8 7 2 2 8 7 0  
  cout << endl;
  // 寻找某个子序列第一次出现地点
  int ia2[] = {2, 8};
  vector<int> iv4(ia2, ia2 + sizeof(ia2) / sizeof(int));
  cout << *search(iv.begin(), iv.end(), iv4.begin(), iv4.end())
       << endl;                                            //2
  // 寻找连续出现2个8的子序列的起点
  cout << *search_n(iv.begin(), iv.end(), 2, 8)            //8
       << endl; 
  // 寻找连续出现3个小于8的子序列的起点
  cout << *search_n(iv.begin(), iv.end(), 3, 8, less<int>())
       << endl;                                            //7
  // 将两个区间的元素互换，第二个区间的元素个数不应小于第一个区间的元素个数
  swap_ranges(iv4.begin(), iv4.end(), iv.begin());
  for_each(iv.begin(), iv.end(), display<int>());          //2 8 2 8 7 10 8 8 7 2 8  
  cout << endl;
  for_each(iv4.begin(), iv4.end(), display<int>());        //7 2  
  cout << endl;
  // 改变区间的值全部减2
  transform(iv.begin(), iv.end(), iv.begin(), bind2nd(minus<int>(), 2));
  for_each(iv.begin(), iv.end(), display<int>());          //0 6 0 6 5 8 6 6 5 0 6  
  cout << endl;
  // 改变区间的值，令第二个区间的元素加到第一个区间的对应元素身上
  // 第二个区间的元素个数不应小于第一个区间的元素个数
  transform(iv.begin(), iv.end(), iv.begin(), iv.begin(), (plus<int>()));
  for_each(iv.begin(), iv.end(), display<int>());          //0 12 0 12 10 16 12 12 10 0 12  
  cout << endl;
  // **************************************************************//
  
  vector<int> iv5(ia, ia + sizeof(ia) / sizeof(int));
  vector<int> iv6(ia + 4, ia + 8);
  vector<int> iv7(15);
  for_each(iv5.begin(), iv5.end(), display<int>());        //0 1 2 3 4 5 6 6 6 7 8  
  cout << endl;
  for_each(iv6.begin(), iv6.end(), display<int>());        //4 5 6 6 
  cout << endl;
  
  cout << *max_element(iv5.begin(), iv5.end()) << endl;    //8
  cout << *min_element(iv5.begin(), iv5.end()) << endl;    //0
  // 判断是否iv6内的所有元素都出现于iv5中
  // 注意: 两个序列都必须是sorted ranges
  cout << includes(iv5.begin(), iv5.end(), iv6.begin(), iv6.end()) << endl;  //1
  // 将两个序列合并为一个序列
  // 注意: 两个序列都必须是sorted ranges, 获得的结果也是sorted 
  merge(iv5.begin(), iv5.end(), iv6.begin(), iv6.end(), iv7.begin());
  for_each(iv7.begin(), iv7.end(), display<int>());        //0 1 2 3 4 4 5 5 6 6 6 6 6 7 8 
  cout<<endl;
  // 符合条件的元素放在容器的前段, 不符合的元素放在后段，不能保证原相对次序
  partition(iv7.begin(), iv7.end(), even());
  for_each(iv7.begin(), iv7.end(), display<int>());        //0 8 2 6 4 4 6 6 6 6 5 5 3 7 1 
  cout<<endl;
  // 去除连续而重复的元素，注意: 获得的结果可能有残余数据
  unique(iv5.begin(), iv5.end());
  for_each(iv5.begin(), iv5.end(), display<int>());        //0 1 2 3 4 5 6 7 8 7 8 后面的两位为残余部分
  cout<<endl;
  // 去除连续而重复的元素，将结果置于另一处，注意: 获得的结果可能有残余数据
  unique_copy(iv5.begin(), iv5.end(), iv7.begin());
  for_each(iv7.begin(), iv7.end(), display<int>());        //0 1 2 3 4 5 6 7 8 7 8 5 3 7 1  后面的为残余部分
  cout<<endl;
  stable_partition(iv7.begin(),iv7.end(),even());
  for_each(iv7.begin(), iv7.end(), display<int>());        //0 2 4 6 8 8 1 3 5 7 7 5 3 7 1 
  cout<<endl;
  sort(iv7.begin(), iv7.end());
  vector<int>::iterator ud = unique(iv7.begin(), iv7.end()); //iv7要是有序的
  iv7.erase(ud, iv7.end());
  for_each(iv7.begin(), iv7.end(), display<int>());        //0 1 2 3 4 5 6 7 8 
  cout<<endl;

      return 0;
}
