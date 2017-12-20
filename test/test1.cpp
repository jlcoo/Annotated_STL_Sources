#include <iostream>
#include <vector>
#include <string>

using namespace std;

template <typename T> class Test{  
public:  
    static std::string info;  
};
// template <> string Test<int>::info("123");   //OK 
// template <typename T> string Test<T>::info("123");   //OK 
// template <typename T> string Test<T>::info;        //OK 
template <> string Test<int>::info;            //OK 
// template <> string Test<int>::info();      //error 
// template <typename T> string Test<T>::info();   //error 


int main(int argc, char const *argv[])
{
  vector<int, std::allocator<int>> iv;

  // vector<int, allocator<int> > ie;  //这么写可以在g++中编译通过

  return 0;
}
