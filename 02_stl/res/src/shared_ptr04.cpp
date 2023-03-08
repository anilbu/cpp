#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"
#include "person.h"


class Myclass: public std::enable_shared_from_this<Myclass> {
public:
    Myclass()
    {
        std::cout << "Myclass()  this = " << this << '\n';
    }

    ~Myclass()
    {
        std::cout << "~Myclass() this = " << this << '\n';
    }

    void func()
    {
        // *this nesnesinin hayatini kontrol eden shared_ptr'nin (bu ornekte sp nesnesi) 
        // kopyasini cikarmak istiyoruz
        auto sptr = shared_from_this();
        std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';
        std::cout << "sptr.get() = " << sptr.get() << '\n';

    }
};


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto sp = make_shared<Myclass>();
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';

        sp->func();
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    }
    std::cout << "-----------------------------\n";
    {
        Myclass m;
        
        try
        {
            m.func();
        }
        catch(const std::bad_weak_ptr& e)
        {
            std::cerr << e.what() << '\n';
        }
    }
}
