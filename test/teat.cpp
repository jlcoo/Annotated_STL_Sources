#include <iostream>
using namespace std;

template<typename T>
class A
{
public:
    A(T a)
    {
        this->a = a;
    }

    template<typename U> //加上这句就可以了
    friend A<U> operator+(A<U> &a1, A<U> &a2);

    T getA(){
        return this->a;
    }
private:
    T a;
};

template<typename T>
A<T> operator+(A<T> &a1, A<T> &a2){
    T a = a1.a + a2.a;
    A<T> tmp(a);
    return tmp;
}

int main()
{
    A<int> a1(2);
    A<int> a2(4);
    A<int> a3 = a1 + a2;

    cout << a3.getA() << endl;

    return 0;
}