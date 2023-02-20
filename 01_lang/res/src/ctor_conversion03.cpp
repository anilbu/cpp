#include <iostream>

class Myclass {
public:
    explicit Myclass(int) 
    {
        std::cout << "explicit Myclass(int)\n";
    }
    
    Myclass(double) 
    {
        std::cout << "Myclass(double)\n";
    }
};

int main(int argc, char const *argv[])
{
    Myclass x = 12;
    Myclass x(12);
}
