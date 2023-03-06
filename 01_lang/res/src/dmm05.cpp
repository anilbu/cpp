#include <iostream>
#include <vector>

struct Nec {
    Nec(){
        std::cout << "Nec()  = " << this << '\n';
    }
    
    ~Nec(){
        std::cout << "~Nec() = " << this << '\n';
    }
    unsigned char buffer[16]{};
};

int main(int argc, char const *argv[])
{
    int n = 4;
    auto p = new Nec[n];
    
    delete[] p;
}