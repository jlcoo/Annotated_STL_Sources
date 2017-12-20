#include <functional>
#include <iostream>
using namespace std;
int main(){
  greater<int> ig;
  cout<<boolalpha<<ig(4,6);
  cout<<greater<int>()(6,4);
}










