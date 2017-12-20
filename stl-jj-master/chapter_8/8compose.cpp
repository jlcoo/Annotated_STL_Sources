// file : 8compose.cpp
// gcc2.91[o]bcb4[x] vc6[x]
// compose 是gcc提供的

#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>
#include <iterator>
using namespace std;

int main()
{
// 将outite 绑定到cout 每次对outite 指派一个元素 然后接一个 " ".
	ostream_iterator<int> outite(cout, " ");
	
	int ia[6] = {2, 21, 12, 7, 19, 23};
	vector<int> iv(ia, ia+6);

// 欲于每个元素v 身上执行(V+2)*3
// 注意。 for_each() 是nonmutating algorithm. 元素内容不能更改
// 所以， 执行之后 iv 内容不变
for_each(iv.begin(), iv.end(), composel(bind2nd(multiplies<int>(),3), bind2nd(plus<int>(),2)));
copy(iv.begin(), iv.end(), outite);
cout << endl;

// 如果像这样， 输注另一个地点（cout） 是可以的
transform(iv.begin(), iv.end(), outite, composel(bind2nd(multiplies<int>(),3), bind2nd(plus<int>(),2) ));
cout<< endl; 
// 12 69 42 27 63 75 

}
