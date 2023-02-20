#include <iostream>

class Base {
public:
    Base() = default;
    Base(const Base& other)
    {
        std::cout << "Base copy ctor\n";
    }
    
    Base(Base&& other)
    {
        std::cout << "Base move ctor\n";
    }
};

class Der: public Base {
    // Derleyicinin urettigi copy ctor
    // Der(const Der& other) : Base(other) {}
    
    // Derleyicinin urettigi move ctor
    // Der(Der&& other) : Base(std::move(other)) {}
};


int main(int argc, char const *argv[])
{
    Der d1;
    Der d2 = d1;
    Der d3 = std::move(d1);
}
