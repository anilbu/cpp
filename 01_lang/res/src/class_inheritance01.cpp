#include <iostream>

class Member
{
public:
    Member()
    {
        std::cout << "Member default ctor this = " << this << '\n';
    }

    ~Member()
    {
        std::cout << "Member dtor\n";
    }
};

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
public:
    Der()
    {
        std::cout << "Der default ctor this = " << this << '\n';
    }

    ~Der()
    {
        std::cout << "Der dtor\n";
    }
private:
    Member mx;
};

int main(int argc, char const *argv[])
{
    Der der;
}
