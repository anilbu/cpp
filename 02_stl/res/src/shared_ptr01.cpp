#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        std::cout << "sizeof(void*) = " << sizeof(void*) << '\n';
        std::cout << "sizeof(unique_ptr<string>) = " << sizeof(unique_ptr<string>) << '\n';
        std::cout << "sizeof(shared_ptr<string>) = " << sizeof(shared_ptr<string>) << '\n';
    }
    std::cout << "------------------------------\n";
    {
        shared_ptr<string> sp1{ new string{ "obj1" } };
        auto sp2 = make_shared<string>("obj2");
    }
    std::cout << "------------------------------\n";
    {
        auto f_deleter = [](string* str) {
            std::cout << *str << " delete ediliyor\n";
            delete str;
        };

        shared_ptr<string> sptr{ new string{ "obj1" }, f_deleter};
    }
}
