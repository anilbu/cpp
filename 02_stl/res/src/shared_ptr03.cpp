#include <iostream>
#include <memory>
#include <algorithm>
#include <string>
#include <list>
#include <vector>
#include "nutility.h"
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        auto sp = make_shared<string>("obj1");
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';

        auto x = sp;
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';

        auto y = x;
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';

        auto z = y;
        std::cout << "sp.use_count() = " << sp.use_count() << '\n';
    }
    std::cout << "------------------------------\n";
    {
        auto sp1 = make_shared<Person>("person1");
        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';

        auto sp2 = sp1;
        auto sp3 = sp2;

        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
        std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';

        sp2.reset();
        std::cout << "sp2.reset()\n";

        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
        std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';

        sp3.reset();
        std::cout << "sp3.reset()\n";

        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
        std::cout << "sp3.use_count() = " << sp3.use_count() << '\n';
    }
    std::cout << "------------------------------\n";
    {
        auto sp1 = make_shared<Person>(Person{ "person1" });

        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';

        {
            auto sp2 = sp1;
            std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
            std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';

            {
                auto sp3 = sp2;
                auto sp4 = sp3;
                std::cout << "sp3.use_count() = " << sp3.use_count() << '\n';
            }
            std::cout << "sp2.use_count() = " << sp2.use_count() << '\n';
        }
        std::cout << "sp1.use_count() = " << sp1.use_count() << '\n';
    }
    std::cout << "--------------------\n";
    {
        list<shared_ptr<Person>> plist;

        for (size_t i = 0; i < 3; i++)
        {
            plist.emplace_back(new Person{ rname() });
        }

        vector<shared_ptr<Person>> pvec{plist.begin(), plist.end()};
        sort(pvec.begin(), pvec.end(), [](const auto& a, const auto& b) {
            return *a < *b;
        });

        printp(plist);
        printp(pvec);
    }
    std::cout << "--------------------\n";
    {
        shared_ptr<Person> p1 { new Person{ "person" }};
        shared_ptr<Person> p2 { new Person{ "person" }};

        cout << boolalpha;

        std::cout << "(p1 == p2) = " << (p1 == p2) << '\n';
        std::cout << "(*p1 == *p2) = " << (*p1 == *p2) << '\n';
        
        std::cout << "p1.use_count() = " << p1.use_count() << '\n';
        std::cout << "p2.use_count() = " << p2.use_count() << '\n';
    }
    std::cout << "--------------------\n";
    {
        shared_ptr<Person> p1 { new Person{ "person1" }};
        shared_ptr<Person> p2 { new Person{ "person2" }};
        
        std::cout << "p1.use_count() = " << p1.use_count() << '\n';
        std::cout << "p2.use_count() = " << p2.use_count() << '\n';
        
        p1 = p2;
        
        std::cout << "p1.use_count() = " << p1.use_count() << '\n';
        std::cout << "p2.use_count() = " << p2.use_count() << '\n';
    }
    std::cout << "--------------------\n";
    {
        shared_ptr<Person> p1 { new Person{ "person1" }};
        auto p2 = p1;
        auto p3 = p1;
        auto p4 = p1;
                
        std::cout << "p1.use_count() = " << p1.use_count() << '\n';
        std::cout << "p2.use_count() = " << p2.use_count() << '\n';
        
        p1.reset();
        
        std::cout << "p1.use_count() = " << p1.use_count() << '\n';
        std::cout << "p2.use_count() = " << p2.use_count() << '\n';
    }
    
}
