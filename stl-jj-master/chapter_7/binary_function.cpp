template<class Arg1, class Arg2, class result>
struct binary_function
{
	typedef Arg1 first_argument_type;
	typedef Arg2 second_argument_type;
	typedef result result_argument_type;
};

tempalte <class T>
struct plus : public binary_function<T, T, T>
{

	T operator() (const T& x, const T& y) const {return x + y;}
};

// 二元仿函数转换成一元仿函数

template <class operation>
class binder1st
...
protected:
	operation op;
	typename operation::first_argument_type value;
public:
	typenmae operation::result_type
	operation()(const typename operation::second_argument_type& x)cosnt 
	{ ... }
};
