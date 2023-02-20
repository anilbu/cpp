#include <iostream>

class Nec
{
public:
    Nec()
    {
        std::cout << "default ctor this = " << this << '\n';
    }

    ~Nec()
    {
        std::cout << "dtor this = " << this << '\n';
    }
};

void foo(Nec n)
{
    std::cout << "foo cagrildi &n = " << &n << '\n';
}

int main(int argc, char const *argv[])
{
    Nec mnec;

    foo(mnec);  // arguman copy ctor ile cagriliyor.
    (void) getchar();
}
