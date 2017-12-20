#include <map>
#include <iostream>
#include <string>
using namespace std;

int main(int argc, char const *argv[])
{
  map<string, int> simap;
  simap[string("jjhou")] = 1;
  simap[string("jerry")] = 2;
  simap[string("jason")] = 3;
  simap[string("jimmy")] = 4;

  pair<string, int> value(string("david"), 5);
  simap.insert(value);

  map<string, int>::iterator simap_iter = simap.begin();
  for(; simap_iter != simap.end(); ++simap_iter)
    cout << simap_iter->first << ' '
         << simap_iter->second << endl; // david 5
                                        // jason 3
                                        // jerry 2
                                        // jimmy 4
                                        // jjhou 1
  int number = simap[string("jjhou")];
  cout << number << endl;               // 1
  map<string, int>::iterator ite1;
  ite1 = simap.find(string("mchen"));
  if(ite1 == simap.end())
    cout << "mchen not found!" << endl; // mchen not found!

  ite1 = simap.find(string("jerry"));
  if(ite1 != simap.end())
    cout << "jerry found!" << endl;     // jerry found!

  ite1->second = 9;
  int number2 = simap[string("jerry")];
  cout << number2 << endl;              // 9

  return 0;
}
