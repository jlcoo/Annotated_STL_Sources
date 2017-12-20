// file : 8functor-adapter.cpp
#include <algorithm>
#include <functional>
#include <vector>
#include <iostream>

using namespace std;
void print(int i)
{
	cout << i << ' ' ;
}

class Int
{
public:
 explicit Int(int i): m_i(i) { }
// 这里有个既存的成员函数（稍后希望于 STL 体系中被复用）
 void print1() const {cout <<'[' << m_i << ']';}
private:
 int m_i;
};

int main()
{
// 将outite 绑定到cout 每次对outite指派一个元素， 然后接一个 " ".
 ostream_iterator<int> outite(cout, " ");
 int ia[6] = {2, 21, 12, 7, 19, 23};
 vector<int> iv(ia, ia+6);
// 找出不小于12的元素个数
 cout << count_if(iv.begin(), iv.end(), not1(bind2nd(multiples<int>(),3), bind2nd(plus<int>(),2) ));
 cout << endl; // 4 

// 令每个元素 v 执行 （v+2）*3 然后输注 outite
 transform(iv.begin(), iv.end(), outite, composel(bind2nd(multiplies<int>(),3), bind2nd(plus<int>(),2) ));
 cout << endl; // 12 69 42 27 63 75 

// 以下将所有元素拷贝到 outite. 有数种方法
 copy (iv.begin(), iv.end(), outite);
 cout << endl;

// (1) 以下 以函数指针搭配STL算法
 for_each(iv.begin(), iv.end(), print);
 cout << endl;

// (2) 以下 以修饰过的一般函数单配STL 算法
 for_each(iv.begin(), iv.end(), ptr_fun(print));
 cout << endl;

 Int t1(3), t2(7), t3(20), t4(14), t5(68);
 vector<int> Iv;
 Iv.push_back(t1);
 Iv.push_back(t2);
 Iv.push_back(t3);
 Iv.push_back(t4);
 Iv.push_back(t5);

// (3) 以下 以修饰的成员函数搭配STL算法
 for_each(Iv.begin(), Iv.end(), mem_fun_ref(&Int::print1));
// [3] [7] [20] [14] [68]
}
