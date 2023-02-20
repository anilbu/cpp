#include <iostream>

int main(int argc, char const *argv[])
{
    int i = 10;
    const int ci = 20;

    {
        decltype(i) x;              // decltype(i) = int
        decltype(ci) x = 99;        // decltype(ci) = const int
    }
    {
        auto& r{ i };
        decltype(r) x = i;          // decltype(r) = int&
    }
    {
        const auto& r = i;
        decltype(r) x = i;          // decltype(r) = const int&
    }
    {
        struct Nec { int a; };

        Nec nec;
        decltype(nec.a) x;          // decltype(nec.a) = int
    }
    {
        using mytype = decltype(i);
    }
    {
        decltype(i) foo();
    }
}
