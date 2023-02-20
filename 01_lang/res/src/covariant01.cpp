#include <iostream>

class Base {
public:
    virtual void print()
    {
        std::cout << "Base\n";
    }
};
class Der: public Base {
public:
    virtual void print() override
    {
        std::cout << "Der\n";
    }
};

class B {
public:
    virtual Base* create_obj() {
        return new Base;
    }
};

class A: public B {
public:
    virtual Der* create_obj() override {
        return new Der;
    }
};

int main(int argc, char const *argv[])
{
    A ax;
    Der* p = ax.create_obj();
    p->print();
    
    
    B& baseref = ax;
    Base* ret = baseref.create_obj();   // Gercekte foo islevi bir Der* donduruyor
    ret->print();
}
