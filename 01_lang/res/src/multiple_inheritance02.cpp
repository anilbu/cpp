#include <iostream>

class Base {
public:
    void base_func() { std::cout << "Base::base_func()\n"; }
};

class Der1: public Base {
public:

};

class Der2: public Base {
public:

};

class MDer: public Der1, public Der2 {
public:
    void func()
    {
        // base_func();      // syntax error: Der1::base_func or Der2::base_func?
        Der1::base_func();   // gecerli: Der1::base_func
        Der2::base_func();   // gecerli: Der2::base_func
    }
};

int main(int argc, char const *argv[])
{
    MDer mder;
    // mder.base_func();      // syntax error: which one?
    mder.Der1::base_func();   // gecerli
    mder.Der2::base_func();   // gecerli

    // Base& baseref1 = mder;                   // sentaks hatasi
    Base& baseref2 = static_cast<Der1&>(mder);  // gecerli: Baseref = Der1::Base
    Base& baseref3 = static_cast<Der2&>(mder);  // gecerli: Baseref = Der2::Base
}
