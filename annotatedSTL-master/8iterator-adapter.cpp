#include <iterator>
#include <deque>
#include <algorithm>
#include <iostream>
using namespace std;
int main(  ){
  ostream_iterator<int> outite( cout," " );
int ia[  ]=  {
  0,1,2,3,4,5
};

 deque<int> id( ia,ia+6 );


 copy( id.begin(),id.end(),outite );
 cout<<endl;
 copy( ia+1,ia+2,front_inserter(id) );
 copy(ia+3,ia+5,back_inserter(id));
 copy( id.begin(),id.end(),outite );
 cout<<endl;
}
