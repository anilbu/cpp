#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        // default ctor
        vector<int> ivec;

        std::cout << "ivec.size() = " << ivec.size() << '\n';
        std::cout << "ivec.empty() = " << ivec.empty() << '\n';
    }
    std::cout << "------------------------\n";
    {
        // size_t
        vector<int> ivec(10);
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
    std::cout << "------------------------\n";
    {
        // (3) fill ctor
        vector<string> svec(10, "####");
        std::cout << "svec.size() = " << svec.size() << '\n';
        print(svec, " ");
    }
    std::cout << "------------------------\n";
    {
        // (4) copy ctor (deep)
        vector<int> ivec1(10);
        vector<int> ivec2{ ivec1 };
        vector<int> ivec3(ivec1);
        vector<int> ivec4 = ivec1;
        auto ivec5 = ivec1;
        auto ivec6{ ivec1 };

        std::cout << "ivec1.size() = " << ivec1.size() << '\n';
        std::cout << "ivec2.size() = " << ivec2.size() << '\n';
    }
    std::cout << "------------------------\n";
    {
        // (5) move ctor
        vector<int> ivec1(10);

        vector<int> ivec2{ std::move(ivec1) };
        vector<int> ivec3(std::move(ivec2));
        vector<int> ivec4 = std::move(ivec3);
        auto ivec5 = std::move(ivec4);
        auto ivec6{ std::move(ivec5) };

        std::cout << "ivec1.size() = " << ivec1.size() << '\n';
        std::cout << "ivec6.size() = " << ivec6.size() << '\n';
    }
    std::cout << "------------------------\n";
    {
        // (6) initializer_list ctor
        list<const char*> slist { "murat", "fatma", "isa", "fahri", "anil"};
    
        std::cout << "slist.size() = " << slist.size() << '\n';
    }
    std::cout << "------------------------\n";
    {
        // range ctor
        list<const char*> slist { "murat", "fatma", "isa", "fahri", "anil"};
    
        // vector<string> svec = list; // gecersiz: farkli turlerden containerlar birbirine atanamaz
        vector<string> svec(slist.begin(), slist.end());
    }
    std::cout << "------------------------\n";

}
