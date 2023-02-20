#include <iostream>

class Date
{
public:
    Date() = default; // Eger Default ctor belirtilmeseydi, not-declared olacakti.

    Date(int d, int m, int y) : md{d}, mm{m}, my{y}
    {
    }

    // Date(const Date &other) : md{other.md}, mm{other.mm}, my{other.my}
    // {
    //     std::cout << "this = " << this << '\n';
    //     std::cout << "&other = " << &other << '\n';
    // }

    void print() const
    {
        std::cout << md << '-' << mm << '-' << my << '\n';
    }

private:
    int md{1}, mm{1}, my{1900};
};

int main(int argc, char const *argv[])
{

    Date dx{12, 8, 1999};
    dx.print();

    Date dy = dx; // copy ctor: Derleyici tarafindan default edildi.
    dy.print();

    Date dz;
    
    std::cout << "&dy = " << &dy << '\n';
    std::cout << "&dx = " << &dx << '\n';
    
    
    return 0;
}
