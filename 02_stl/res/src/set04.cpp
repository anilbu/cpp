#include <iostream>
#include <string>
#include <set>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        multiset<string> smset{};
        rfill(smset, 500, rtown);

        auto nFound = smset.count("istanbul");
        std::cout << "nFound = " << nFound << '\n';
    }
    {
        set<string> smset{};
        rfill(smset, 20, rtown);

        auto nFound = smset.count("istanbul");
        std::cout << "nFound = " << nFound << '\n';
    }
}
