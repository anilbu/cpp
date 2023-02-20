#include <iostream>

/*
   Asagidaki baglamda Photocopier sinif turunden bir nesnenin 
   tek bir device olarak ele alinmasi istenmektedir. 
*/

class Device {
public:
    virtual void turn_on() {
        std::cout << "Device::turn_on\n";
    }
    
    virtual void turn_off() {
        std::cout << "Device::turn_off\n";
    }
};

class Printer : virtual public Device {
public:
    void print() {
        std::cout << "Printer::print\n";
    }
    
    virtual void turn_on() override {
        std::cout << "Printer::turn_on\n";
    }
    
    virtual void turn_off() override {
        std::cout << "Printer::turn_off\n";
    }
};

class Scanner : virtual public Device {
public:
    void scan() {
        std::cout << "Scanner::scan\n";
    }
    
    virtual void turn_on() override {
        std::cout << "Scanner::turn_on\n";
    }
    
    virtual void turn_off() override {
        std::cout << "Scanner::turn_off\n";
    }
};

class Photocopier : public Printer, public Scanner {
public:
    virtual void turn_on() override {
        std::cout << "Photocopier::turn_on\n";
    }
    
    virtual void turn_off() override {
        std::cout << "Photocopier::turn_off\n";
    }
};

int main(int argc, char const *argv[])
{
    Photocopier ps;
    
    ps.turn_on();
    
    ps.print();
    ps.scan();
    
    ps.turn_off();
    
    Printer& pr = ps;
    pr.turn_on();
    pr.print();
    pr.turn_off();
}
