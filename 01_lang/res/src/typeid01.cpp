#include <iostream>
#include <typeinfo>
#include <boost/core/demangle.hpp>

int main(int argc, char const *argv[])
{
    using namespace std;
    using boost::core::demangle;
    
    int x = 10;
    cout << boolalpha;
    cout << (typeid(int) == typeid(int)) << '\n';
    cout << (typeid(int) == typeid(x)) << '\n';
    cout << (typeid(double) == typeid(x)) << '\n';
    
    
    cout << demangle(typeid(int).name()) << '\n';
}
