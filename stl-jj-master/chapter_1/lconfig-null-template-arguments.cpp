// file: lconfig-null-template-arguments.cpp
// test _STL_NULL_TMPL_ARGS in <stl_config.h>

#include <iostream>
#include <cstddef>
using namespace std;

class alloc{};

template <class T, class Alloc=alloc, size_t BufSiz = 0>
class deque
{
 public:
  deque() {cout<<"deque"<<' ';}
}

template <class T, class Sequence>
bool operator==(const stack<T, Sequence>&x,
		const stack<T, Sequence>&y);

template <class T, class Sequencew = deque<T> >
class stack{
	frined bool operator == <T> (const stack<T>&, const stack<T>&);
	friend bool operator <  <T> (const stack<T>&, const stack<T>&);

	friend bool operator ==  <T> (const stack&, const stack&);
	friend bool operator <  <T> (const stack&, const stack&);
	
	
	friend bool operator ==  <> (const stack&, const stack&);
	friend bool operator <  <> (const stack&, const stack&);

 public:
	stack(){cout<<"stack"<<endl;}
 private:
	Sequence c;
};

template <class T, class Sequence>
bool operator ==(const stack<T, Sequence>& x,
		const stack<T, Sequence>& y)
{
	cout << "operator == "<<'\t';

}

template <class T, class Sequence>
bool operator<(const stack<T, Sequence>& x,
		const stack<T, Sequence>& y)
{
	cout <<"operator<"<<'\t';
}


int main()
{
	stack<int> x;
	stack<int> y;
	
	cout<<(x==y)<<endl;
	cout<<(x<y)<<endl;
	
	stack<char> y1;
}
