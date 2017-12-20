#include <iostream>
using namespace std;

class alloc {
};

template <class T, class Alloc = alloc>
class vector {
public:
  void swap(vector<T, Alloc>&) {
    cout << "swap()" << endl;
  }
};

#ifdef __STL_FUNCTION_TMPL_PARTIAL_ORDER
template <class T, class Alloc>
inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) {
  cout << "__STL_FUNCTION_TMPL_PARTIAL_ORDER" << endl;
  x.swap(y);
}
#endif

int main(int argc, char const *argv[])
{
  vector<int> x, y;
  swap(x, y);
  
  return 0;
}
