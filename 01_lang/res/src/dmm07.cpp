#include <iostream>
#include <new>
#include <vector>


struct Nec {
    Nec(){
        std::cout << "Nec() = " << this << '\n';
    }
    
    ~Nec(){
        std::cout << "~Nec() = " << this << '\n';
    }
    unsigned char buffer[16]{};
};

int main(int argc, char const *argv[])
{
    std::cout << "sizeof(Nec) = " << sizeof(Nec) << '\n';
    
    auto p = new (std::nothrow) Nec;
    std::cout << "p = " << p << '\n';
    
    p->~Nec();
}