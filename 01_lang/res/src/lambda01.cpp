#include <iostream>

using namespace std;


int main(int argc, char const *argv[])
{
    int a = 0;
    int b = 0;
    
    auto f = [a, &b]() mutable {
        a++;
        b++;
        return a + b;
    };
    
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "f() = " << f() << '\n';
    
    
    
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
    std::cout << "f() = " << f() << '\n';
    
    
    std::cout << "a = " << a << '\n';
    std::cout << "b = " << b << '\n';
}
