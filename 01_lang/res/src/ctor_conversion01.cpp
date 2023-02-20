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
        std::cout << "\tthis = " << this << '\n';
        std::cout << "\t&other = " << &other << '\n';
        return *this;
    }
    
    explicit Myclass(double x)
    {
        std::cout << "Myclass(double x) x = " << x << " this = " << this << '\n';
    }
};

int main(int argc, char const *argv[])
{
    {
        Myclass m;
        m = 12;
        // m = Myclass{12};
        std::cout << "scope bitiyor\n";
    }

    std::cout << "main devam ediyor\n";
}
