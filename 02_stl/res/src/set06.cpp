#include <iostream>
#include <string>
#include <set>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<string> sset;
        rfill(sset, 10, rtown);

        std::cout << "sset.size() = " << sset.size() << '\n';
        print(sset);

        sset.erase(sset.begin());

        std::cout << "sset.size() = " << sset.size() << '\n';
        print(sset);
    }
    {
        set<string> sset;
        rfill(sset, 10, rtown);

        std::cout << "sset.size() = " << sset.size() << '\n';
        print(sset);

        sset.erase(sset.begin(), prev(sset.end(), 5));

        std::cout << "sset.size() = " << sset.size() << '\n';
        print(sset);
    }
    {
        multiset<string> smset;
        rfill(smset, 30, rtown);

        std::cout << "sset.size() = " << smset.size() << '\n';
        print(smset);
        
        auto nDeleted = smset.erase("istanbul");
        
        std::cout << "nDeleted = " << nDeleted << '\n';
        std::cout << "sset.size() = " << smset.size() << '\n';
        print(smset);
    }
}
