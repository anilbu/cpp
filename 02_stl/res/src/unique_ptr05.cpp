#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "nutility.h"
#include "person.h"

Person* create_object_raw()
{
    static size_t n = 0;
    return new Person("obj" + std::to_string(n++));
}

std::unique_ptr<Person> create_object()
{
    static size_t n = 0;
    return std::make_unique<Person>("obj" + std::to_string(n++));
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto p = create_object_raw();
        std::cout << "*p = " << *p << '\n';
        std::cout << "Nesne delete edilmedigi icin destroy edilmeyecek\n";
    }
    std::cout << "-----------------------------\n";
    {
        auto p = create_object();
        std::cout << "*p = " << *p << '\n';
        std::cout << "Nesne destroy ediliyor\n";
    }
    std::cout << "-----------------------------\n";
}
