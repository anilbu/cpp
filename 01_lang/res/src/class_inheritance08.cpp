#include <iostream>

class Base {
public:
    Base& operator=(const Base&)
    {
        std::cout << "Base copy assignment\n";
        return *this;
    }

    Base& operator=(Base&&)
    {
        std::cout << "Base move assignment\n";
        return *this;
    }
};

class Der: public Base {
public:
    Der& operator=(const Der& other)
    {
        std::cout << "Der copy assignment\n";
        Base::operator=(other);
        //alternative
        // *(Base*)this = other;
        return *this;
    }

    Der& operator=(Der&& other)
    {
        std::cout << "Der move assignment\n";
        Base::operator=(std::move(other));
        //alternative
        // *(Base*)this = std::move(other);
        return *this;
    }
};

class Der2: public Base {
public:
    Base& operator=(const Base&)
    {
        std::cout << "Der2 copy assignment\n";
        return *this;
    }

    Base& operator=(Base&&)
    {
        std::cout << "Der2 move assignment\n";
        return *this;
    }
};


int main(int argc, char const *argv[])
{
    Der d1;
    Der d2;

    d2 = d1;
    d2 = std::move(d1);

    std::cout << "------------------\n";

    Der2 d3;
    Der2 d4;

    d4 = d2;
    d4 = std::move(d2);

}
