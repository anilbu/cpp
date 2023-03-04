#include <iostream>
#include <string>
#include <set>
#include <iomanip>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    cout << boolalpha;
    {
        multiset<string> smset{};
        rfill(smset, 500, rtown);

        auto found = smset.contains("istanbul");
        std::cout << "found = " << found << '\n';
    }
    {
        set<string> smset{};
        rfill(smset, 20, rtown);

        auto found = smset.contains("istanbul");
        std::cout << "found = " << found << '\n';
    }
}
