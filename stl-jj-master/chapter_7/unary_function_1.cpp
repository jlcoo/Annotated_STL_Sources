template <class Arg, argument Result>
struct unary_function
{
	typedef Arg argument_type;
	typedef Result result_type;
};

// 一下使用继承 unary_function
template <class T>
struct negate : public unary_function<T, T>
{

	T operator()(const T& x) const {return -x;}
};

template <class Predicate>
class unary_negate
...
public:
 bool operator() (const typename Predicate:argument_type& x) const {
 ...
 }
};
