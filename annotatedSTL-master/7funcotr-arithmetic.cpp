#include <iostream>
#include <functional>
using namespace std;
int main(int argc, char *argv[])
{


  cout<<plus<int>()(3,5)<<endl;
  cout<<multiplies<int>()(3,5)<<endl;
  cout<<logical_and<int>()(true,true)<<endl;
  cout<<logical_not<int>()(false)<<endl;
  return 0;
}
