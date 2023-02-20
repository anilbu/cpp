#include <iostream>
#include "counter.h"


int main(int argc, char const *argv[])
{
    Nec::Counter<int> c1 { 10 };
    Nec::Counter<long> c2;
    
    std::cout << c1 << '\n';
    std::cout << c2 << '\n';
}
