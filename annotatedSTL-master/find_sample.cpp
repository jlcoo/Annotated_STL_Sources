#include <algorithm>
#include <iostream>
using namespace std;
int main(){
  const int arraySize=7;
  int ia[arraySize]= {0,1,2,3,4,5,6};
  int* end = ia+arraySize;
  int*ip = find(ia,end,4);
  if(ip==end)
    std::cout<<"4 not found"<<end;
  else
    std::cout<<"4 found."<<*ip<<endl;
}
