#include <iostream>
#include <algorithm>
#include <deque>
#include <iomanip>
#include <cstdlib>


using namespace std;
void Print(int a)
{
    cout << std::setw(4) <<a;

}

int main( )
{
    deque<int> ideq(20, 9);              //  alloc只适用于G++编译器
    cout <<"size = " << ideq.size() << endl;     //size = 20
    /// 现在构造了一个deque, 有20个int元素, 初值皆为9
    /// 缓冲区大小为32byte

    ///  为每个元素设定新值
    for(int i = 0; i < ideq.size(); i++)  
    {
        ideq[i] = i;
    }

    for(auto &x : ideq)
        cout << x << ' ';     // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 
    cout <<endl;
    ideq.push_back(3);
    for(auto &x : ideq)
        cout << x << ' ';     // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 3 
    cout << endl;
    for(int i = 0; i < 3; ++i)
        ideq.push_back(i);
    for(auto &x : ideq)
        cout << x << ' ';     // 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 3 0 1 2 
    cout << endl;
    cout << "size = " << ideq.size() << endl; //size = 24
    // 在最前端增加一个元素，其值是99
    ideq.push_front(99);  //会配置一个新的连续块空间（map的新节点）
    for(auto &x : ideq)
        cout << x << ' ';    // 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 3 0 1 2 
    cout << endl;
    cout << "size = " << ideq.size() << endl;  // size = 25
    // 最前面增加2个元素，其值分别为98,97
    ideq.push_front(98);
    ideq.push_front(97);
    for(auto &x : ideq)
        cout << x << ' ';   // 97 98 99 0 1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16 17 18 19 3 0 1 2
    cout << endl;
    cout << "size = " << ideq.size() << endl; // size = 27
    // 搜索数值为99的元素，并打印出来
    deque<int>::iterator itr;
    itr = find(ideq.begin(), ideq.end(), 99);   //99
    cout << *itr << endl;                       //99
    cout << *(itr._M_cur) << endl;

    return 0;
}

