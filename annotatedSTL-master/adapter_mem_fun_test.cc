#include <iostream>
#include <vector>
#include <algorithm>
#include <functional>
using namespace std;
class Shape{
public :virtual void display( )=0;
};

  class Rect:public Shape{
  public :virtual void display(  ){
    cout<<"Rect";
  }
  };
 class  Circel:public Shape{
  public :virtual void display(  ){
    cout<<"Circel";
  }
 };
 class  Square:public Rect{
  public :virtual void display(  ){
    cout<<"Square";
  }
 };

   int main( ) {
     vector<Shape*> V;
     V.push_back(new Rect(  ));
     V.push_back(new Circel(  ));
     V.push_back( new Square(  ) );

     V.push_back( new Square(  ) );
     V.push_back(new Rect(  ));
     for_each(V.begin(), V.end(), mem_fun( &Shape::display ));
     cout<<endl;

   }


















