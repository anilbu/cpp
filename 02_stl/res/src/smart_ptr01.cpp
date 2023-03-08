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

int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        try
        {
            auto p = new Myclass{"naked ptr"};
            throw runtime_error{"demo"};
            delete p;
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
            auto p = make_unique<Myclass>("smart_ptr");
            throw runtime_error{"demo"};
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
