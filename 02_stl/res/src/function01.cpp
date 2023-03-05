#include <iostream>
#include <functional>
#include "nutility.h"

int func(int a) {
    return a * a;
}

std::function<int(int)> create_func()
{
    return [](int x) { return x * x; };
}

class Functor {
public:
    int operator()(int x) { 
        std::cout << "Functor::operator()(int x) x = " << x << '\n';
        return x + 1000;
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        function<void(void)> f1;    // void(void)
        function<int(int)> f2;      // int(int)
        function<int(int)> f3 = func;
        function<int(int)> f4 = [](int a) { return a + a;};
        function<int(int)> f5 = +[](int a) { return a + a;};
        function<int(int)> f6 = Functor{};
        
    }
    {
        std::function<int(int)> f;
        std::cout << (f ? "dolu" : "bos") << '\n';

        f = func;
        std::cout << (f ? "dolu" : "bos") << '\n';
    }
    {
        function<int(int)> f = func;
        auto val = f(10);
        std::cout << "val = " << val << '\n';
    }
    {
        std::function<int(int)> f;
        try
        {
            auto x = f(12);
        }
        catch (const std::bad_function_call& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    {
        auto f = create_func();
        std::cout << f(10) << '\n';
    }
}
