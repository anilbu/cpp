#include <iostream>
#include <memory>
#include "nutility.h"
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    auto sptr = make_shared<Person>("person3");
    std::cout << "*sptr = " << *sptr << '\n';
    std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';

    weak_ptr<Person> wptr{ sptr };

    sptr.reset();

    if (auto sp = wptr.lock()) {
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';
        std::cout << "*sp = " << *sp << '\n';
    }
    else{
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    }
}
