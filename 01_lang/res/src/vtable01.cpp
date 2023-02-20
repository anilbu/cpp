#include <iostream>

class NonpolymorphicClass {
    int x{};
    int y{};
    void func();
};

class Base {
    int x{};
    int y{};
    virtual void func1();
};

class Der : public Base {
    virtual void func1() override;
    virtual void func2();
};


int main(int argc, char const *argv[])
{
    std::cout << "sizeof(int) = " << sizeof(int) << '\n';
    std::cout << "sizeof(int*) = " << sizeof(int*) << '\n';
    std::cout << "sizeof(NonpolymorphicClass) = " << sizeof(NonpolymorphicClass) << '\n';
    std::cout << "sizeof(Base) = " << sizeof(Base) << '\n';
    std::cout << "sizeof(Der) = " << sizeof(Der) << '\n';
}
