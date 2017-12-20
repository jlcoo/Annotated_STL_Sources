#include <iostream>
#include <algorithm>
#include <iterator>
using namespace std;

template <typename BidirectionalIter>
void mergesort(BidirectionalIter first, BidirectionalIter last) {
  typename iterator_traits<BidirectionalIter>::difference_type n 
                                             = distance(first, last);
  if (n == 0 || n == 1)
    return;
  else {
    BidirectionalIter mid = first + n / 2;
    mergesort(first, mid);
    mergesort(mid, last);
    inplace_merge(first, mid, last); 
  }
}


int main(int argc, char const *argv[])
{
  vector<int> iv{1, 9 ,6, 4, 8, 3, 5, 2, 7};
  mergesort(iv.begin(), iv.end());

  copy(iv.begin(), iv.end(), ostream_iterator<int>(cout, " "));     //1 2 3 4 5 6 7 8 9 
  cout << endl;

  return 0;
}

