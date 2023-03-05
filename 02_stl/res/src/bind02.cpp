#include <iostream>
#include <functional>

void func(int &r)
{
    r *= 10;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::placeholders;

    {
        int x = 50;
        
        // Bind'in urettigi callable nesnenin member'i degerini x'den copy ile aliyor
        auto f = bind(func, x);
        f();
        std::cout << "x = " << x << '\n';
    }

    {
        int x = 50;
        auto f = bind(func, ref(x));
        f();
        std::cout << "x = " << x << '\n';
    }
}