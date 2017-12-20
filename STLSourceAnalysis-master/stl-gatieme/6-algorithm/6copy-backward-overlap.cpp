// 测试copy_backward算法函数
#include <iostream>
#include <algorithm>
#include <deque>              //deque拥有随机访问迭代器(random access iterator)
using namespace std;

template <class T>
struct display
{
  void operator()(const T& x){
    cout << x << ' ';
  }
};
int main(int argc, char *argv[])
{
  {
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    copy_backward(ia + 2, ia + 7, ia + 9);   //输出区间的终点(就逆向而言)与输入区间重叠，没问题
    for_each(ia, ia + 9, display<int>());  //0 1 2 3 2 3 4 5 6 
    cout << endl; 
  }

  {   //利用有效作用域
    int ia[] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
    copy_backward(ia + 2, ia + 7, ia + 5); //输出区间的起点与输入区间重叠，可能会有问题
    for_each(ia, ia + 9, display<int>());   //2 3 4 5 6 5 6 7 8 
    cout << endl; //输出结果正确，因为调用的copy算法使用memmove()执行实际复制操作
  }

  {
    int ia[]={0, 1, 2, 3, 4, 5, 6, 7, 8};
    deque<int> id(ia, ia+9);
    deque<int>::iterator first = id.begin();
    deque<int>::iterator last  =  id.end();
    ++++first;                 //相当于advance(first, 2);
    cout<< *first << endl;     //2
    ----last;                  //相当于advance(last, -2);
    cout<< *last << endl;      //7，因为区间一般是左闭右开，last在哨兵处
    // advance(first, 2);
    // advance(last, -2);
    // cout<< *first << endl;     
    // cout<< *last << endl;

    deque<int>::iterator result = id.end();
    cout << *result << endl;  //0  
    copy_backward(first, last, result);//输出区间的终点与输入区间重叠，没问题
    for_each(id.begin(), id.end(), display<int>()); //0 1 2 3 2 3 4 5 6
    cout << endl;
  }

  {
    int ia[]={0, 1, 2, 3, 4, 5, 6, 7, 8};
    deque<int> id(ia, ia+9);
    deque<int>::iterator first = id.begin();
    deque<int>::iterator last  =  id.end();

    advance(first, 2);                                //2
    cout<< *first << endl;
    advance(last, -2);                                //7
    cout<< *last << endl;

    deque<int>::iterator result = id.begin();
    advance(result, 5);                               //5
    cout << *result << endl;

    copy_backward(first, last, result);                          //输出区间的起点与输入区间重叠，可能会有问题
    for_each(id.begin(), id.end(), display<int>());   //2 3 4 5 6 5 6 7 8  
    cout << endl;   //输出结果正确，因为调用的copy算法使用memmove()执行实际复制操作
  }

  return 0;
}