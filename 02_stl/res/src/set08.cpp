#include <iostream>
#include <string>
#include <set>
#include "nutility.h"
#include "date.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<Date> dset;

        if (auto [iter, success] = dset.emplace(12, 12, 2022); success) {
            std::cout << "*iter = " << *iter << '\n';
        }

        auto iter = dset.emplace_hint(dset.begin(), 5, 5, 2020);
        std::cout << "*iter = " << *iter << '\n';

        print(dset, "\n");
    }
    {
        multiset<Date> dset;

        auto iter = dset.emplace(12, 12, 2022);
        std::cout << "*iter = " << *iter << '\n';
        

        iter = dset.emplace_hint(dset.begin(), 5, 5, 2020);
        std::cout << "*iter = " << *iter << '\n';

        print(dset, "\n");
    }
}
