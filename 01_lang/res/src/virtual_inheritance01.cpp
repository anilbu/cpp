#include <iostream>

class Base {
public:
    Base(const char* p) {
        std::cout << "Base(const char*) p = " << p << '\n';
    }
};

class DerA: virtual public Base {
public:
    DerA(): Base("DerA")
    {
    }
};

class DerB: virtual public Base {
public:
    DerB(): Base("DerB")
    {
    }
};

class DerAB: public DerA, public DerB {
public:
    DerAB(): Base("DerAB")
    {
    }
};

class DerDerAB: public DerAB {
public:
    DerDerAB(): Base("DerDerAB")
    {
    }
};


int main(int argc, char const *argv[])
{
    DerA dera;
    std::cout << "------------\n";
    DerAB derab;
    std::cout << "------------\n";
    DerDerAB derderab;
}
