#include <iostream>
#include <cstddef>
// 测试class template可否拥有non-type template参数 (可以)
using namespace std;
class alloc {
};
inline size_t __deque_buf_size(size_t n, size_t sz)
{
  return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template <class T, class Ref, class Ptr, size_t Bufsiz>
struct __deque_iterator {
  typedef __deque_iterator<T, T&, T*, Bufsiz> iterator;
  typedef __deque_iterator<T, const T&, const T*, Bufsiz> const_iterator;
  static size_t buffer_size()
  {
    return __deque_buf_size(Bufsiz, sizeof(T));
  }
};

template <class T, class Alloc = alloc, size_t Bufsiz = 0>
class deque {
public:   //Iterators
  typedef __deque_iterator<T, T&, T*, Bufsiz> iterator;
};

int main(int argc, char const *argv[])
{
  cout << deque<int>::iterator::buffer_size() << endl;              //输出128 = 512/4
  cout << deque<int, alloc, 64>::iterator::buffer_size() << endl;   //64 = 512/(64/8)
 
  return 0;
}
