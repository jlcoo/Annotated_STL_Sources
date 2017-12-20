// file lconfig.cpp
// test configurations defgined in <stl_config.h>
#include <vector>    // which included <stl_algobase.h>
#include <iostream>  // and then <stl_config.h>

using namespace std;

int main()
{
#if defined(_sgi)
 cout<<"_sgi"<<endl;
#endif

#if defined(_GNUC_)
 cout<<"_GNUC_"<<endl;
 cout<<_GNUC_<<' '<<_GNUC_MINOR_<<endl;
#endif

//case 2
#ifdef _STL_NO_DRAND48
 cout<<"_STLNO_DRAND48 defined"<<endl;
#else
 cout<<"_STLNO_DRAND48 undefined"<<endl;
#endif

//case 3
#ifdef _STL_STATIC_TEMPLATE_MEMBER_BUG
 cout<<"_STL_STATIC_TEMPLATE_MEMBER_BUG defined"<<endl;
#else
 cout<<"_STL_STATIC_TEMNPLATE_MEMBER_BUG undefined"<<endl;
#endif

//case 5
#ifdef _STL_CLASS_PARTIAL_SPECIALIZATION
 cout << "_STL_CLASS_PARTIAL_SPECIALIZATION defined"<<endl;
#else
 cout<<"_STL_CLASS_PARTIAL_SPECIALIZATION undefined"<<endl;
#endif
}

