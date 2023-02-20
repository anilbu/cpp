#include <iostream>

class Date
{
public:
    Date() = default; // Eger Default ctor belirtilmeseydi, not-declared olacakti.

    Date(int d, int m, int y) : md{d}, mm{m}, my{y}
    {
    }

    // Derleyicinin urettigi atama fonksiyonu su bicimdedir:
    // Date &operator=(const Date &other)
    // {
    //     std::cout << "operator= called by (this) " << this << '\n';
    //     std::cout << "operator= called with (other) " << &other << '\n';
    //     md = other.md;
    //     mm = other.mm;
    //     my = other.my;
    //     return *this;
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
    Date dy;
    
    std::cout << "&dx = " << &dx << '\n';
    std::cout << "&dy = " << &dy << '\n';
    
    dy = dx;            // dy.operator=(dx);
    
    (dy = dx).print();  // dy.operator=(dx).print()

    dx.print();
    dy.print();
}
