#include <iostream>
#include <fucntional>
using namespace std;

int main()
{
// 一下产生仿函数实体对象
	plus<int>       plusobj;
	minus<int>      minusobj;
	multiplies<int> multiplies;
	divides<int>    dividesobj;
	modulus<int>    modulusobj;
	negate<int>     negateobj;

// 一下运用上述对象 履行函数功能
	cout << plusobj(3, 5) << endl;
	cout << minusobj(3, 5) << endl;
	cout << multipliesobj(3, 5) << endl;
	cout << dividesobj(3, 5) << endl;
	cout << modulusobj(3, 5) << endl;
	cout << negateobj(3)     << endl;

// 一下直接使用仿函数临时对象履行函数功能
// 语法分析： functor<T>() 是一个临时对象， 后面在接一对小括号
// 意指调用 function call operator
	cout << plus<int>()(3, 5) << endl;
	cout << minux<int>()(3,5) << endl;
	cout << multiplies<int>()(3, 5) << endl;
	cout << divides<int>()(3, 5) << endl;
	cout << modulus<int>()(3, 5) << endl;
	cout << negate<int>()(3) << endl; 
}
