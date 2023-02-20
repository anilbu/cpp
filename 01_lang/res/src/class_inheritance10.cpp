#include <iostream>

class Base {
public:
    Base(int)           { std::cout << "Base(int)\n"; }
    Base(int, int)      { std::cout << "Base(int, int)\n"; }
    Base(double)        { std::cout << "Base(double)\n"; }
    void foo()          { std::cout << "Base::foo()\n"; }
    void bar(int)       { std::cout << "Base::bar(int)\n"; }
    void baz(int, int)  { std::cout << "Base::baz(int, int)\n"; }
};

class Der: public Base {
public:
    using Base::Base;   // inherited ctor

    void func()  { std::cout << "Der::func()\n"; }
};

int main(int argc, char const *argv[])
{
    Der der(10);
    Der der2(1, 2);
    Der der3(3.14);

    der.func();
    der.foo();
    der.bar(1);
    der.baz(1, 2);
}
