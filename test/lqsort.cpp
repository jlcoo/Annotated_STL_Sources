#include <cstdlib>
#include <iostream>
using namespace std;

int fcmp( const void* elem1, const void* elem2);

int main(int argc, char const *argv[])
{
  int ia[10] = {32, 92, 67, 58, 10, 4, 25, 52, 59, 54};
  for(int i = 0; i < 10; ++i)
    cout << ia[i] << ' ';
  cout << endl;

  qsort(ia, sizeof(ia)/sizeof(int), sizeof(int), fcmp);

  for(int i = 0; i < 10; ++i)
    cout << ia[i] << ' ';
  cout << endl;

  return 0;
}

int fcmp( const void* elem1, const void* elem2)
{
  const int* i1 = (const int*) elem1;
  const int* i2 = (const int*) elem2;

  if(*i1 < *i2)  //从大到小
    return 1;
  else if (*i1 == *i2)
    return 0;
  else if(*i1 > *i2)  //为1，从小到大
    return -1;
}

