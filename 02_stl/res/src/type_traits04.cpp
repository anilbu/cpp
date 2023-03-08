#include <iostream>
#include <type_traits>
#include "nutility.h"

template<typename T>
void func(T&&) 
{
    if(std::is_lvalue_reference_v<T>) {
        std::cout << "T is lvalue reference\n";
    }
    else{
        std::cout << "T is rvalue reference\n";
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int ival;
    func(ival);
    func(10);
}
