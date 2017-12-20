// plus minus multiplies divides modulus negate
// plus

template <class T>
struct plus : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y) 
	const {retrun x + y;}
};

// minus
template<class T>
struct minus : public bianry_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	const {return x - y;}
};

// multiplies
template <class T>
struct multiplies : public binary_function<T, T, T>
{
	T operator()(const T&x, const T& y)
	const {return  x * y;}
};

// divides
template <class T>
struct divides : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	const {return x / y;}
};

// modulus
template <class T>
struct modulus : public binary_function<T, T, T>
{
	T operator()(const T& x, const T& y)
	const {return x % y;}
};

// neagte
template <class T>
struct negate : public binary_function<T, T, T>
{
	T operator()(const T& x)
	const {return -x;}
};
