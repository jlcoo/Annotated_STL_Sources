#include <iostream>
#include <algorithm>
#include <vector>
#include <iomanip>


using namespace std;
void Print(int a)
{
    cout <<std::setw(4) <<a;

}

int main( )
{
    /// test heap (底层以vector完成)
    int ia[9] = {0, 1, 2, 3, 4, 8, 9, 3, 5};
    vector<int> ivec(ia, ia + 9);  //以vector完成底层

    make_heap(ivec.begin(), ivec.end());
    for(vector<int>::iterator iter = ivec.begin();
        iter != ivec.end();
        iter++)
    {
        cout << setw(4) << *iter;   //9   5   8   3   4   0   2   3   1
    }
    cout << endl;

    ivec.push_back(7);
    push_heap(ivec.begin(), ivec.end());
    for(vector<int>::iterator iter = ivec.begin();
        iter != ivec.end();
        iter++)
    {
        cout << setw(4) << *iter;   //9   7   8   3   5   0   2   3   1   4
    }
    cout << endl;

    // cout << ivec.back() <<endl;
    // ivec.pop_back();

    pop_heap(ivec.begin(), ivec.end());
    cout << ivec.back() <<endl;         //9
    ivec.pop_back();

    sort_heap(ivec.begin(), ivec.end());
    for(vector<int>::iterator iter = ivec.begin();
        iter != ivec.end();
        iter++)
    {
        cout << setw(4) <<*iter;    //0   1   2   3   3   4   5   7   8
    }
    cout << endl;

    // 底层以array完成
    int iar[6] = {4, 1, 7, 6, 2, 5};
    make_heap(iar, iar+6);

    for(auto &x : iar)
        cout << x << ' ';           //7 6 5 1 2 4
    cout << endl;

    return 0;
}

