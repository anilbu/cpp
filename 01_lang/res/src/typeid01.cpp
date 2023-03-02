#include <iostream>
#include <typeinfo>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int x = 10;
    cout << boolalpha;
    cout << (typeid(int) == typeid(int)) << '\n';
    cout << (typeid(int) == typeid(x)) << '\n';
    cout << (typeid(double) == typeid(x)) << '\n';
    
    
    cout << _demangle(typeid(int).name()) << '\n';
}
