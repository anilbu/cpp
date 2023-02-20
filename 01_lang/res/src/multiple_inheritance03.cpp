#include <iostream>

class Device {
public:
    virtual void turn_on() {
        std::cout << "Device::turn_on\n";
    }
    
    virtual void turn_off() {
        std::cout << "Device::turn_off\n";
    }
};

class Printer : public Device {
public:
    void print() {
        std::cout << "Printer::print\n";
    }
};

class Scanner : public Device {
public:
    void scan() {
        std::cout << "Scanner::scan\n";
    }
};

class Photocopier : public Printer, public Scanner {};

int main(int argc, char const *argv[])
{
    Photocopier ps;
    
    ps.Printer::turn_on();
    ps.Scanner::turn_on();
    
    ps.scan();
    ps.print();
    
    ps.Scanner::turn_off();
    ps.Printer::turn_off();
    
    Printer& pr = ps;
    pr.turn_on();
    pr.print();
    pr.turn_off();
}
