#include <iostream>
#include "nutility.h"


template <typename T>
class Base {
public:
    void func()
    {
        std::cout << "Base<T>::func() T = " << _demangle(typeid(T).name()) << "\n";
        auto* pder = static_cast<T*>(this);
        pder->foo();    // Tasarimda T'nin foo fonksiyonu oldugu kabul ediliyor.
    }
};

class Derived: public Base<Derived> {
public:
    void foo() 
    {
        std::cout << "Derived::foo()\n";
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    Derived der;
    der.func();
}
