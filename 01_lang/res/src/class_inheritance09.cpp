#include <iostream>

class Base {
public:
    void func(int)
    {
        std::cout << "Base::func(int x)\n";
    }
    
    void func(int, int)
    {
        std::cout << "Base::func(int, int)\n";
    }

    void func(double)
    {
        std::cout << "Base::func(double)\n";
    }
protected:
    void foo()
    {
        std::cout << "Base::foo()\n";
    }

    inline static int x{};
    int y{};
};

class Der: public Base {
public:
    using Base::func;
    using Base::foo;
    using Base::x;
    using Base::y;

    void func(double) { std::cout << "Der::func(double)\n"; }
};

int main(int argc, char const *argv[])
{
    Der der;
    der.foo();        // legal

    der.func(12);     // legal
    der.func(3.14);   // legal

    der.y = 10;       // legal

    // Base::x = 5;   // illegal: inaccessible
    Der::x = 5;
}
