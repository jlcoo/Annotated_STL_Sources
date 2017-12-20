// 测试hash table ，不知道可以不，因为这是内部结构
#include <hash_set>   //for hashtable
#include <iostream>
#include <cstring>
using namespace std;
struct eqstr
{
  bool operator() (const char* s1, const char* s2) const
  {
    return strcmp(s1, s2) == 0;
  }
};

int main(int argc, char const *argv[])
{
  // hashtable<int,                      //这样声明是不可以的
  //           int,
  //           hash<int>,
  //           identity<int>,
  //           equal_to<int>>   iht(50, hash<int>(), equal_to<int>());

  hash_set<const char*, hash<const char*>, eqstr> set;
  
  return 0;
}
