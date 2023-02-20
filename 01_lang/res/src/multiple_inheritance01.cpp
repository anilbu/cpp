
#include <iostream>

class A {
public:
    A() { std::cout << "A()\n"; };
    
    void foo()                  { std::cout << "A::foo()\n"; }
    void func()                 { std::cout << "A::func()\n"; }
    
    virtual void a_func()       { std::cout << "A::a_func()\n"; }

};

class B {
public:
    B() { std::cout << "B()\n"; };
    
    void bar()                  { std::cout << "B::bar()\n"; }
    void func()                 { std::cout << "B::func()\n"; }
    
    virtual void b_func()       { std::cout << "B::b_func()\n"; }
};

class C: public A, public B {
public:
    C()
    {
        std::cout << "C()\n";
    }
    
    virtual void a_func() override { std::cout << "C::a_func()\n"; }
    virtual void b_func() override { std::cout << "C::b_func()\n"; }
};

int main(int argc, char const *argv[])
{
    C cx;
    
    std::cout << "---------------\n";
    
    cx.foo();
    cx.bar();

    std::cout << "---------------\n";
    
    // cx.func();      // syntax error: ambiguity
    cx.A::func();
    cx.B::func();

    std::cout << "---------------\n";
    
    A* ap = &cx;
    ap->a_func();
    
    B* bp = &cx;
    bp->b_func();

    std::cout << "---------------\n";
}
