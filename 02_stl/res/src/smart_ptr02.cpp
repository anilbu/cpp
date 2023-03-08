#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"

class Myclass {
public:
    Myclass(): tag{ "default" }
    {
        std::cout << "Myclass()\n";
    }

    Myclass(std::string _tag):tag{ std::move(_tag) }
    {
        std::cout << "Myclass() tag = " << tag << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Myclass& m)
    {
        return os << m.tag;
    }

    ~Myclass()
    {
        std::cout << "~Myclass() tag = " << tag << "\n";
    }
private:
    std::string tag;
};

class A {
public:
    A() : mp {new Myclass{"raw ptr"}} 
    {
        throw std::runtime_error{"demo"};
    }
private:
    Myclass* mp;
};

class B {
public:
    B() : mp {new Myclass{"smart ptr"}} 
    {
        throw std::runtime_error{"demo"};
    }
private:
    std::unique_ptr<Myclass> mp;
};


int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        try
        {
            auto obj = A();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
    std::cout << "------------------------------\n";
    {
        try
        {
            auto obj = B();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
