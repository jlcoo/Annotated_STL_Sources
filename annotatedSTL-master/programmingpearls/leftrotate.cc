#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
#include <iterator>
using namespace std;

template <class EuclideanRingElement>
EuclideanRingElement _gcd(EuclideanRingElement m,EuclideanRingElement n){
  EuclideanRingElement t = m%n;
  while(n!=0) {
 m=n; 
 n=t;
}
}

template<class ForwardIterator>
inline void rotate_cxf(ForwardIterator first,ForwardIterator middle,ForwardIterator last){
  if(first==middle||middle==last)
    return;

  _rotate(first,middle,last,Distance_type(first),iterator_category(first));
}


template<class RandomAccessIterator,class Distance>
void _rotate(RandomAccessIterator first,RandomAccessIterator middle,RandomAccessIterator last,Distance *,random_access_iterator_tag)
{
  Distance n = _gcd(last-first, middle-first);

  while(n--){
    _rotate_cycle(first,last,first+n,middle-first,value_type(first));

}
  
}

template<class RandomAccessIterator,class Distance,class T>
void _rotate_cycle(RandomAccessIterator first,RandomAccessIterator last,RandomAccessIterator initial,Distance shift,T*){
  T value = *initial;
  RandomAccessIterator ptr1  = initial;
  RandomAccessIterator ptr2 = ptr1+shift;
  while(ptr2!=initial){
    *ptr1=*ptr2;
    ptr1=ptr2;
    if(last-ptr2>shift)
      ptr2+=shift;
    else
      ptr2 = first+shift-(last-ptr2);
  }
  *ptr1 = value;


}


template<class T>
struct  display{
void operator(  )( const T &x){
  cout<<x<<' ';
}
};

int main(  ){
  
int ia[  ]={
  0,1,2,3,4,5,6,7,8,9,10
};

 vector<int> iv( ia,ia+sizeof( ia )/sizeof( int ) );

 vector<int>::iterator  it =iv.begin()+3; 

 rotate_cxf(iv.begin(),it,iv.end());
 // reverse(iv.begin(  ), it);

 //reverse( it,iv.end(  ) );
 //reverse(iv.begin(  ),iv.end( )  );

 for_each( iv.begin(  ),iv.end(  ),display<int>( )  );
}


















