#include <algorithm>
#include <vector>
#include <functional>
#include <iostream>
using namespace std;

template <class T>
struct display{
  void operator()(const T& x) const
  { cout<< x<<' ';}
};

struct even
{
  bool operator()(int x) const
  { return x%2? false:true;}
};
class even_by_two{
 public:
  int operator()() const
  { return _x+=20;
  }
 private:
  static int _x;

};


int even_by_two::_x= 0;
int main(int argc, char *argv[])
{
  int ia[]={0,2,4,6,8,10,12,12,12,14,16};
  vector<int> iv(ia,ia+sizeof(ia)/sizeof(int));

  // cout<<*adjacent_find(iv.begin(),iv.end())<<endl;
  // cout<<*adjacent_find(iv.begin(),iv.end(),equal_to<int>());
  // cout<< count_if(iv.begin(),iv.end(),bind2nd(less<int>(),20))<<endl;
  // vector<int>::iterator  fd = iv.begin();
  // if((fd = find_if(iv.begin(),iv.end(),bind2nd(greater<int>(),19))) != iv.end()){
  //   cout<<"finding"<<endl;
  //   for_each(fd,iv.end(),display<int>());
  // }else{
  //   cout<<"find failed"<<endl;
  // }
  vector<int> iv2(ia+6,ia+8);

  // vector<int>::iterator  fd = iv.begin();
  // if((fd = find_first_of(iv.begin(),iv.end(),iv2.begin(),iv2.end())) != iv.end()){
  //   cout<<"finding"<<endl;
  //   for_each(fd,iv.end(),display<int>());
  // }else{
  //   cout<<"find failed"<<endl;
  // }
  vector<int> iv3(15);
  //  remove_copy(iv.begin(),iv.end(),iv3.begin(),12);
  //  generate_n(iv.begin(),2,even_by_two());
  //  remove_if(iv.begin(),iv.end(),bind2nd(less<int>(),10));
  // remove_copy_if(iv.begin(),iv.end(),iv3.begin(),bind2nd(less<int>(),10));
  // for_each(iv3.begin(),iv3.end(),display<int>());
  // replace(iv.begin(),iv.end(),10,99);
  // replace_if(iv.begin(),iv.end(),bind2nd(less<int>(),12),-10);
  // for_each(iv.begin(),iv.end(),display<int>());
  // cout<<endl;
  //  reverse(iv.begin(),iv.end());
  //rotate(iv.begin(),iv.begin()+1,iv.end());

  int ia2[]={1,3,5,77,55,31};
  vector<int> iv4(ia2,ia2+sizeof(ia2)/sizeof(int));
  sort(iv4.begin(),iv4.end());
  //  transform(iv.begin(),iv.end(),iv.begin(),bind2nd(minus<int>(),2));
  //  transform(iv.begin(),iv.end(),iv.begin(),iv.begin(),(plus<int>()));
  // swap_ranges(iv4.begin(),iv4.end(),iv.begin());
  // cout<<*max_element(iv.begin(),iv.end())<<endl;
  // cout<<*min_element(iv.begin(),iv.end())<<endl;
  vector<int> iv7(20);
  cout<<  includes(iv.begin(),iv.end(),iv4.begin(),iv4.end())<<endl;
  for_each(iv.begin(),iv.end(),display<int>());
  cout<<endl;
  for_each(iv4.begin(),iv4.end(),display<int>());
  merge(iv.begin(),iv.end(),iv4.begin(),iv4.end(),iv7.begin());
  cout<<endl;
  for_each(iv7.begin(),iv7.end(),display<int>());
  //  partition(iv7.begin(),iv7.end(),even());
  //  stable_partition(iv7.begin(),iv7.end(),even());
  vector<int>::iterator ud = unique(iv7.begin(),iv7.end());
  iv7.erase(ud,iv7.end());
  cout<<endl;
  for_each(iv7.begin(),iv7.end(),display<int>());

      return 0;
}
