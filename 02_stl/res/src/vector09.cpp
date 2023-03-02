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
        vector<string> svec{"ali", "ata", "murat", "serhat"};
        //                                 ^

        print(svec);
        std::cout << "        ^\n";

        svec.insert(svec.begin() + 2, "nihal");
        print(svec);
        std::cout << "        ^\n";
    }
    {
        vector<string> svec{"ali", "ata", "murat", "serhat"};
        for (size_t i = 0; i < 5; ++i)
        {
            svec.insert(svec.begin(), rname());
            print(svec);
        }
    }
    {
        vector<string> svec{"ali", "ata", "murat", "serhat"};

        auto iter = svec.insert(svec.begin() + 1, "TACETTIN");
        std::cout << "*iter = " << *iter << '\n';
        std::cout << "distance(svec.begin(), iter) = " << distance(svec.begin(), iter) << '\n';
        print(svec);
    }
    {
        vector<string> svec{"ali", "ata", "murat", "serhat"};
        auto iter = svec.insert(svec.begin() + 1, {"MUHITTIN", "TACETTIN", "ALEADDIN"});
        std::cout << "*iter = " << *iter << '\n';
        std::cout << "distance(svec.begin(), iter) = " << distance(svec.begin(), iter) << '\n';
        print(svec);
    }
    {
        vector<string> svec{"ali", "ata", "murat", "serhat"};
        svec.insert(svec.begin(), 5, "NURETTIN");
        print(svec);
    }
    {
        vector<string> svec{"ali", "ata", "murat", "serhat"};
        list<string> slist { "BURAK", "LALEGUL", "FERHAT", "RUMEYSA"};
        svec.insert(svec.begin(), slist.begin(), slist.end());
        print(svec);
    }
}
