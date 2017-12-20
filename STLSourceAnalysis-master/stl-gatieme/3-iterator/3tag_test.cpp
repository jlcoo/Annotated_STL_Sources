#include <iostream>
using namespace std;

struct B                ///  B  可比拟为InputIterator
{

};

struct D1 : public B   ///  D1 可比拟为ForwardIteraor
{

};

struct D2 : public D1    //  D2 可比拟为BidirectionalIterator
{

};


template <class I>
void funcs(I &p, B)
{
    std::cout <<"B version..." <<endl;
}

template <class I>
void funcs(I &p, D2)
{
    std::cout <<"D2 version..." <<endl;

}



int main(void)
{
    int *p;
    funcs(p, B());        //  参数B完全吻合, 输出"B version..."
    funcs(p, D1());       //  参数未能完全吻合, 因继承关系调用, 输出"B version..."
    funcs(p, D2());       //  参数D2完全吻合, 输出"D2 version..."



    return 0;
}
