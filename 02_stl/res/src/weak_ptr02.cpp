#include <iostream>
#include <memory>
#include <string>
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto sp = make_shared<Person>("person1");
        weak_ptr<Person> wptr{ sp };
        std::cout << "sp = " << sp << '\n';
        std::cout << "*sp = " << *sp << '\n';


        if (shared_ptr<Person> sptr = wptr.lock()) {
            std::cout << "sptr = " << sptr << '\n';
            std::cout << "sp.use_count() = " << sp.use_count() << '\n';
            std::cout << "*sptr = " << *sptr << '\n';
        }

        sp.reset();
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';

        if (auto sptr = wptr.lock(); !sptr) {
            std::cout << "sptr = " << sptr << '\n';
            std::cout << "sp.use_count() = " << sp.use_count() << '\n';
        }
    }
    std::cout << "-----------------\n";
    {
        auto sp = make_shared<Person>("person1");
        sp.reset();
        weak_ptr<Person> wptr{ sp };
    }
}