#include <iostream>
#include <functional>

int func(int x, int y)
{
    std::cout << "int func(int x, int y) x = " << x << " y = " << y << '\n';
    return 1;
}

class Myclass
{
public:
    static int s_func(int x, int y)
    {
        std::cout << "int Myclass::s_func(int x, int y) x = " << x << " y = " << y << '\n';
        return 2;
    }

    int func(int x, int y)
    {
        std::cout << "int Myclass::func(int x, int y) x = " << x << " y = " << y << '\n';
        std::cout << "this = " << this << '\n';

        return 3;
    }
};

int main(int argc, char const *argv[])
{
    {

        int val = 0;

        val = std::invoke(func, 10, 20);
        std::cout << "val = " << val << '\n';

        val = std::invoke(Myclass::s_func, 10, 20);
        std::cout << "val = " << val << '\n';

        Myclass m;
        std::cout << "&m = " << &m << '\n';

        val = std::invoke(&Myclass::func, m, 10, 20);
        std::cout << "val = " << val << '\n';
    }
    {
        Myclass m;
        std::cout << "&m = " << &m << '\n';

        auto fptr = &Myclass::func;

        auto val1 = std::invoke(fptr, m, 30, 50);

        Myclass* mp{ &m };
        auto val2 = std::invoke(fptr, mp, 30, 50);
    }
}
