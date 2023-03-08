#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"
#include "person.h"

void func(std::unique_ptr<Person> uptr)
{
    std::cout << "*uptr = " << *uptr << '\n';
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        unique_ptr<Person> uptr{ new Person{ "obj1" }};
        func(move(uptr));
    }
    std::cout << "-----------------------------\n";
    {
        func(unique_ptr<Person>{ new Person{ "obj2" }});
    }
    std::cout << "-----------------------------\n";
    {
        func(make_unique<Person>("obj3"));
    }
}
