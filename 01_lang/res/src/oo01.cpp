#include <iostream>
#include "cint.h"

int main(int argc, char const *argv[])
{
    std::cout << Cint{ 23 };
    operator<<(std::cout, Cint{ 23 });

    Cint x{ 12 };
    std::cout << x;

    operator>>(std::cin, x);
    std::cin >> x;
}