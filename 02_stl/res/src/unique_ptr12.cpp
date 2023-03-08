#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        auto uptr1 = make_unique<string>("obj");
        auto uptr2 = make_unique<string>("obj");
        
        std::cout << "uptr1 = " << uptr1 << '\n';
        std::cout << "uptr1.get() = " << uptr1.get() << '\n';
        
        std::cout << "(uptr1 == uptr1) = " << (uptr1 == uptr1) << '\n';
        std::cout << "(uptr1 == uptr2) = " << (uptr1 == uptr2) << '\n';
        
        // uptr1 == uptr2.get();   // sentaks hatasi: unique_ptr<string> ile string* karsilastirilamaz.
    }
}
