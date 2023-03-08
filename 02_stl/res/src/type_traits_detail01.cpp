#include <iostream>
#include "nutility.h"

template <typename T>
struct IsInteger {
    static constexpr bool value = false;
};

template <>
struct IsInteger<int> {
    static constexpr bool value = true;
};

template <>
struct IsInteger<unsigned int> {
    static constexpr bool value = true;
};

template <>
struct IsInteger<long int> {
    static constexpr bool value = true;
};

template <typename T>
void func(T x)
{
    // T bir tam sayi turu mu?
    constexpr bool result = IsInteger<T>::value;

    std::cout << "IsInteger<T>::value [with T = " << _demangle(typeid(T).name()) << "| = " << IsInteger<T>::value << "\n";
}

int main(int argc, char const *argv[])
{
    constexpr auto b1 = IsInteger<double>::value;
    constexpr auto b2 = IsInteger<int>::value;

    std::cout << std::boolalpha;
    
    int ival{};
    
    func(ival);
    func(12);
    func(12U);
    func(3.14);
}
