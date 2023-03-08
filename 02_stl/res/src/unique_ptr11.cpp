#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"
#include "person.h"

std::unique_ptr<Person> func(std::unique_ptr<Person> uptr)
{
    std::cout << "*uptr = " << *uptr << '\n';
    return uptr;
}


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto uptr = func(unique_ptr<Person>{ new Person{ "obj2" }});
    }
    std::cout << "-----------------------------\n";
    {
        unique_ptr<Person> uptr{ new Person{ "obj1" }};
        uptr = func(move(uptr));
    }
}
