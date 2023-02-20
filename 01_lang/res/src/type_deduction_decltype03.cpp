#include <iostream>

int f1();
int& f2();
int&& f3();

int main(int argc, char const *argv[])
{
    int i = 10;
    {
        decltype(10) x;             // x = int&
    }
    {
        int* p = &i;
        decltype(*p) x = i;         // x = int&   *p => Lvalue
    }
    {
        decltype(i++) x1;           // x1 = int    i++ => prvalue
        decltype(++i) x2 = i;       // x2 = int&   ++i => lvalue
    }
    {
        int a[5];
        decltype(a) x1;             // x = int[5]   a bir isim
        decltype(a[0]) x2 = a[1];   // x = int&     a[0] => lvalue
    }
    {
        decltype(f1()) x1;          // x1 = int     f1() => prvalue
        decltype(f2()) x2 = i;      // x2 = int&    f1() => lvalue
        decltype(f3()) x3 = 0;      // x3 = int&&   f1() => xvalue
    }
}
