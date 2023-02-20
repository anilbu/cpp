#include <iostream>

class Base {
public:
    virtual ~Base() {
        std::cout << "~Base()\n";
    }
};

class Der: public Base {
public:
    ~Der() override {
        std::cout << "~Der()\n";
    }
};

int main(int argc, char const *argv[])
{
    Der* derptr = new Der;
    delete derptr;      // ~Der() cagrildi
                        // ~Base() cagrildi
    
    std::cout << "--------------\n";
    
    Base* baseptr = new Der;
    delete baseptr;     // ~Der() cagrildi
                        // ~Base() cagrildi
}
