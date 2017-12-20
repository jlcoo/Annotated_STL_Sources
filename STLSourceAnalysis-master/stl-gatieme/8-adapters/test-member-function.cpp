// 测试泛型和多态
#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;

class Shape{
public: 
  virtual void display() = 0;
};

class Rect: public Shape{
public:
  virtual void display(){
    cout << "Rect ";
  }
};
class  Circel: public Shape{
public:
  virtual void display(){
    cout << "Circel ";
  }
};
class  Square: public Rect{
public:
  virtual void display(){
    cout << "Square ";
  }
};

int main() {
  vector<Shape*> V;
  V.push_back(new Rect());
  V.push_back(new Circel());
  V.push_back( new Square());

  V.push_back(new Square());
  V.push_back(new Rect());
  // polymorphically 多态
  for(int i = 0; i < V.size(); ++i)
    (V[i])->display();                                      //Rect Circel Square Square Rect 
  cout << endl;
  // for_each(V.begin(), V.end(), mem_fun(Shape::display)); 不能这样写，一定要以配接器mem_fun修饰member function才能被算法for_each接受
  for_each(V.begin(), V.end(), mem_fun( &Shape::display )); //Rect Circel Square Square Rect 
  cout << endl;

  return 0;
}

