#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "nutility.h"
#include "person.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        // raw_ptr_resource_leak
        vector<Person*> mvec;

        for (int i = 0; i < 3; ++i)
        {
            mvec.emplace_back(new Person("obj" + std::to_string(i)));
        }

        mvec.erase(mvec.begin());
        std::cout << "Vector'un ilk ogesi silindi ancak destroy edilmedi!\n";
        std::cout << "mvec.size() = " << mvec.size() << '\n';
        std::cout << "Vector destroy edildi ancak ogeler destroy edilmedi!\n";
    }
    std::cout << "-----------------------------\n";
    {
        using PersonPtr = std::unique_ptr<Person>;

        vector<PersonPtr> mvec;

        mvec.push_back(unique_ptr<Person>{new Person("obj1")});
        mvec.push_back(make_unique<Person>("obj2"));
        mvec.emplace_back(new Person("obj3"));

        mvec.erase(mvec.begin());
        std::cout << "Vector'un ilk ogesi silindi ve destroy edildi.\n";
        std::cout << "mvec.size() = " << mvec.size() << '\n';
        std::cout << "Vector destroy edildi ve nesneler destroy edildi.\n";
    }
    std::cout << "-----------------------------\n";
}
