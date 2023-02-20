#include <iostream>
#include <string>

class Myclass
{
public:
    Myclass()
    {
        std::cout << "Myclass default ctor this = " << this << '\n';
    }

    ~Myclass()
    {
        std::cout << "Myclass dtor this = " << this << '\n';
    }

    // sinifin conversion ctor
    Myclass(int x)
    {
        std::cout << "Myclass(int x) this = " << this << '\n';
    }
    
    Myclass& operator=(const Myclass& other) {
        std::cout << "copy assignment func\n";
        std::cout << "this = " << this << '\n';
        std::cout << "&other = " << &other << '\n';
        return *this;
    }
    
    explicit Myclass(double x)
    {
        std::cout << "Myclass(double x) x = " << x << " this = " << this << '\n';
    }
};

int main(int argc, char const *argv[])
{
    Myclass m1;
    m1 = 3.14;   // DIKKAT: int'e user-defined conversion yapiliyor, cunku double explicit
    
    Myclass m2;
    m2 = static_cast<Myclass>(3.14);    // double conv_ctor cagrilir
}
