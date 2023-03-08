#include <iostream>
#include <memory>
#include "nutility.h"

struct A;

struct B {
    B() { std::cout << "B()\n"; }
    ~B() { std::cout << "~B()\n"; }

    std::shared_ptr<A> a_ptr;
};

struct A {
    A() { std::cout << "A()\n"; }
    ~A() { std::cout << "~A()\n"; }

    std::shared_ptr<B> b_ptr;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        shared_ptr<A> a{ new A };
        shared_ptr<B> b{ new B };
        
        std::cout << "a.use_count() = " << a.use_count() << '\n';
        std::cout << "b.use_count() = " << b.use_count() << '\n';
    }
    std::cout << "main devam ediyor ve kaynaklar release edildi.\n";
    {
        shared_ptr<A> a{ new A };
        shared_ptr<B> b{ new B };

        a->b_ptr = b;
        b->a_ptr = a;
        
        std::cout << "a.use_count() = " << a.use_count() << '\n';
        std::cout << "b.use_count() = " << b.use_count() << '\n';
    }
    std::cout << "main devam ediyor ve kaynaklar release edilemedi!\n";
}
