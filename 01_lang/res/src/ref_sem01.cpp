#include <iostream>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        int x = 10;
        int& r = x;

        std::cout << "typeid(r).name() = " << _demangle(typeid(r).name()) << '\n';
        std::cout << "(&x == &r) = " << (&x == &r) << '\n';

        int* p = &x;

        std::cout << "typeid(p).name() = " << _demangle(typeid(p).name()) << '\n';
        std::cout << "typeid(*p).name() = " << _demangle(typeid(*p).name()) << '\n';
    }
    
    {
        unsigned int uval{ 56U };
        // int& r = uval;                       // syntax error: type mismatch
        // int& r = static_cast<int>(uval);     // syntax error: must be lvalue
        // int& r = (int) uval;                 // syntax error: must be lvalue
    }

    {
        int a[5]{ 0 };
        int* p = a;
        int r = *p;        // gecerli: *p int turunden bir lvcalue expr
    }
}
