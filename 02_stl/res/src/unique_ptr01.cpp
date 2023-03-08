#include <iostream>
#include <memory>
#include "date.h"

class Myclass {
public:
    int* p{};
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        std::cout << "sizeof(int*) = " << sizeof(int*) << '\n';
        std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
        std::cout << "sizeof(unique_ptr<Myclass>) = " << sizeof(unique_ptr<Myclass>) << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Myclass> up1;                // default initialize
        unique_ptr<Myclass> up2{};              // value initialize
        unique_ptr<Myclass> up3{ nullptr };
        
        auto up4 = make_unique<string>();
        auto up5 = make_unique<string>(20, '*');
    }
    std::cout << "---------------------\n";
    {
        auto p = new Date{ 12, 12, 1982 };

        // Ayni kaynagi birden fazla unique_ptr ile kontrol etmeyin!
        // unique_ptr<Date> x{ p };
        // unique_ptr<Date> y{ p };
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Myclass[]> uptr(new Myclass[5]);
    }
}