#include <iostream>
#include <functional> // std::bind

int func(int x, int y)
{
    std::cout << "func(int, int) x = " << x << " y = " << y << "\n";
    return x * y;
}

int sum(int x, int y, int z)
{
    std::cout << "x = " << x << '\n';
    std::cout << "y = " << y << '\n';
    std::cout << "z = " << z << '\n';

    return x + y + z;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::placeholders;

    {
        auto f = bind(func, 10, 20);
        auto val = f();
        std::cout << "val = " << val << '\n';
    }
    {
        auto f = bind(func, 10, placeholders::_1);  // f'in ilk argumani, func'un 2.parametresi
        std::cout << "f(60) = " << f(60) << '\n';
        
    }
    {
        auto f = bind(sum, _1, _2, _3);
        std::cout << "f(5, 9, 14) = " << f(5, 9, 14) << '\n';
    }
    {
        auto f = bind(sum, _3, _1, _2);
        std::cout << "f(5, 9, 14) = " << f(5, 9, 14) << '\n';
        
    }
    {
        auto f = bind(sum, _1, _1, _1);
        std::cout << "f(10) = " << f(10) << '\n';
        
    }
}