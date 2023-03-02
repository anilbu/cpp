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
        vector<string> svec{"ali", "selim", "ata", "murat", "serhat", "yesim", "serhat", "gizem", "seyhan"};
        std::cout << "svec.size() = " << svec.size() << '\n';
        print(svec);

        auto iter = svec.erase(svec.begin() + 1);
        std::cout << "*iter = " << *iter << '\n';
        std::cout << "svec.size() = " << svec.size() << '\n';
        print(svec);
    }
    {
        vector<string> svec{"ali", "selim", "ata", "murat", "serhat", "yesim", "serhat", "gizem", "seyhan"};
        
        while(!svec.empty())
        {
            print(svec);
            svec.erase(svec.begin());
        }
    }
}
