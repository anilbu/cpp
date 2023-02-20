#include <iostream>
#include <boost/core/demangle.hpp>

using boost::core::demangle;

template <typename T>
void foo(T x) {
    std::cout << "foo<" << demangle(typeid(T).name()) << ">(" << x << ")\n";
}

template <typename T>
void bar(T x) {
    std::cout << "bar<" << demangle(typeid(T).name()) << ">(" << x << ")\n";
}

template <typename T>
void swap(T& a, T& b) {
    std::cout << "swap<" << demangle(typeid(T).name()) << ">(" << a << ", " << b << ")\n";
}


template <typename T>
void func(T x, T y)
{
    std::cout << "func<" << demangle(typeid(T).name()) << ">(" << x << ", " << y << ")\n";
    
    foo(x);
    bar(y);
    swap(x, y);
}

int main(int argc, char const *argv[])
{
    func(12, 56);
}
