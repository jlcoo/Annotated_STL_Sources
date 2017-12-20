#include <iostream>
using namespace std;
class alloc {
};
// 测试class template之内是否可再有template (members)
template <class T, class Alloc = alloc>
class vector {
public:
  typedef T value_type;
  typedef value_type* iterator;

  template <class I>
  void insert(iterator position, I first, I last) {  //重载vector模板类的insert成员函数
    cout << "insert()" << endl;
  };

  void swap(vector<T, Alloc>&) {
    cout << "swap()" << endl;
  }
};


int main(int argc, char const *argv[])
{
  int ia[5] = {0, 1, 2, 3, 4};
  vector<int> x;
  vector<int>::iterator ite;
  x.insert(ite, ia, ia + 5);      //输出insert()

  return 0;
}
