#include <iostream>

class Base {
protected:
    ~Base() {
        std::cout << "~Base()\n";
    }
};

class Der: public Base {
public:
    virtual ~Der() {
        std::cout << "~Der()\n";
    }
};

int main(int argc, char const *argv[])
{
    Der* derptr = new Der;
    Base* baseptr = derptr;
    
    //delete baseptr;   // sentaks hatasi: Bu nesneyi taban sinif uzerinden silmeye calisma
    delete derptr;      // ~Der() cagrildi
                        // ~Base() cagrildi
}
