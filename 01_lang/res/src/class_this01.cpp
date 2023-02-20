#include <iostream>

class Myclass {
public:
    void f();
    
    void func(int x) 
    {
        x = x;          // self assignment
        this->x = x;    // Myclass::x = x;
    }
    
    Myclass f1() { 
        return *this;
    }
    Myclass* f2() { 
        return this;
    }
    Myclass& f3() { 
        return *this;
    }
    
private: 
    int x;
    int y;
};

void foo(Myclass*);
void bar(Myclass);
void baz(Myclass&);

void Myclass::f() { 
    foo(this);
    bar(*this);
    baz(*this);
}

int main(int argc, char const *argv[])
{
    int x = 10;
    int* ptr = &x;
    
    // *ptr demek x demek
    
    
    Myclass m;
    
    m.f();
}
