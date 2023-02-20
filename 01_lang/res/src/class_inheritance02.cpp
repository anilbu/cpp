#include <iostream>


class Base
{
public:
    Base()
    {
        std::cout << "Base default ctor this = " << this << '\n';
    }

    ~Base()
    {
        std::cout << "Base dtor\n";
    }
};

class Der: public Base
{
};

int main(int argc, char const *argv[])
{
    Der der;
    std::cout << "&der = " << &der << '\n';
}
