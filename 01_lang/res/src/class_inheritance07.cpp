#include <iostream>

class Base {
public:
    Base& operator=(const Base&)
    {
        std::cout << "Base copy assignment\n";
        return *this;
    }

    Base& operator=(Base&&)
    {
        std::cout << "Base move assignment\n";
        return *this;
    }
};

class Der: public Base {};

int main(int argc, char const *argv[])
{
    Der d1;
    Der d2;

    d2 = d1;
    d2 = std::move(d1);
}
