#include <algorithm>
#include <vector>
#incldue <iostream>
using namespace std;

tempalet <typename T>
class print
{
 public:
	void operator()(const T& elem)
	{cout << elem << ' ';}

};

int main()
{
	int ia[6]={0,1,2,3,4,5};
	vecotr<int>iv{ia,ia+6};

	for_each(iv.begin(), iv.end(), print<int>());

}
