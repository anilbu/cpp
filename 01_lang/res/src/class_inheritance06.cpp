#include <iostream>

class Base {
public:
    Base()
    {
        std::cout << "Base default ctor\n";
    }

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
public:
    Der() {
        std::cout << "Der default ctor\n";
    }

    // Base copy ctor initializer liste eklenmeseydi Base default ctor cagrilacakti
    Der(const Der& other): Base(other)
    {
        std::cout << "Der copy ctor\n";
    }

    // Base copy ctor initializer liste eklenmeseydi Base default ctor cagrilacakti
    Der(Der&& other): Base(std::move(other))
    {
        std::cout << "Der move ctor\n";
    }
};

class Der2: public Base {
public:
    Der2() {
        std::cout << "Der2 default ctor\n";
    }

    Der2(const Der& other)
    {
        std::cout << "Der2 copy ctor\n";
    }

    Der2(Der&& other)
    {
        std::cout << "Der2 move ctor\n";
    }
};



int main(int argc, char const *argv[])
{
    Der d1;
    Der d2 = d1;
    Der d3 = std::move(d1);
    
    std::cout << "----------\n";
    
    Der2 d4;
    Der2 d5 = d1;
    Der2 d6 = std::move(d4);
}
