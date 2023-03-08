#include <iostream>
#include <memory>
#include <string>
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto sptr = make_shared<Person>("person1");
        std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';
        cout << *sptr << '\n';

        weak_ptr<Person> wptr{ sptr };
        std::cout << "wptr.expired() = " << wptr.expired() << '\n';

        sptr.reset();
        std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';

        std::cout << "wptr.expired() = " << wptr.expired() << '\n';
    }
    std::cout << "------------------------------------\n";
    {
        auto sptr = make_shared<Person>("person3");
        std::cout << "*sptr = " << *sptr << '\n';
        std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';

        weak_ptr<Person> wptr{ sptr };

        sptr.reset();

        if (!wptr.expired())
        {
            shared_ptr<Person> sp{ wptr };
            std::cout << "*sp = " << *sp << '\n';
        }
    }
    std::cout << "------------------------------------\n";
    {
        auto sptr = make_shared<Person>("person2");
        weak_ptr<Person> wptr{ sptr };

        sptr.reset();
        std::cout << "sptr.use_count() = " << sptr.use_count() << '\n';
        std::cout << "sptr = " << sptr << '\n';

        try {
            // gecerli ancak sptr bos ise exception throw edilecek
            shared_ptr<Person> sp { wptr };
            std::cout << "sp = " << sp << '\n';
        }
        catch (const std::bad_weak_ptr& ex) {
            std::cout << "Exception caught: " << ex.what() << '\n';
        }
    }

}
