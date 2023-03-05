#include <iostream>
#include <functional>
#include <vector>
#include "nutility.h"
#include <algorithm>
#include <fstream>
#include <iterator>

class Myclass {
public:
    void foo() const { 
        std::cout << "Myclass::func()\n";
    }
    
    void bar(int a) const {
        std::cout << "Myclass::foo(int) a = " << a << '\n';
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::placeholders;

    Myclass mx;
    
    auto f1 = std::bind(&Myclass::foo, _1);
    f1(mx);
    
    auto f2 = std::bind(&Myclass::bar, _1, _2);
    f2(mx, 55);
    
    auto f3 = std::bind(&Myclass::bar, mx, _1);
    f3(55);
}