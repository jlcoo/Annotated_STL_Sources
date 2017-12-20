// file: 2jjalloc.cpp
// VC6[0], BCB4[o], Gcc2.9[x].
#include "2jjalloc.h"
#include <vector>
#include <iostream>

using namespace std;

int main()
{
 int ia[5] = {0,1,2,3,4};
 unsigned int i;

 vector<int, JJ::alllocator<int> >iv(ia, ia+5);
 for(i=0; i<iv.size(); i++)
 	cout << iv(i) << ' ';
 cout << endl;
}
