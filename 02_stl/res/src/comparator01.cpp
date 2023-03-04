#include <iostream>
#include <string>
#include <set>
#include <functional>
#include "nutility.h"

bool customStringCompareFn(const std::string &a, const std::string &b)
{
    return (a.length() < b.length()) || (a.length() == b.length() && a < b);
}

template <typename T>
using gset = std::set<T, greater<T>>;

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        class CustomStringComparator
        {
        public:
            bool operator()(const std::string &a, const std::string &b) const
            {
                return (a.length() < b.length()) || (a.length() == b.length() && a < b);
            }
        };

        set<string, CustomStringComparator> sset;
        for (int i = 0; i < 20; ++i)
        {
            sset.insert(rname() + ' ' + rfname());
        }
        print(sset, "\n");
    }
    {
        // set<string, bool(*)(const string&, const string&)> sset(customStringCompareFn);
        set<string, decltype(&customStringCompareFn)> sset(customStringCompareFn);
        for (int i = 0; i < 20; ++i)
        {
            sset.insert(rname() + ' ' + rfname());
        }
        print(sset, "\n");
    }
    {
        auto cStrComp = [](const string &a, const string &b)
        {
            return (a.length() < b.length()) || (a.length() == b.length() && a < b);
        };

        // C++20 icin gecerli, C++17 sentaks hatasi
        //      C++17'de lambda ifadelerin default ctor'u deleted
        // set<string, decltype(cStrComp)> sset3();  
        
        set<string, decltype(cStrComp)> sset(cStrComp);
        for (int i = 0; i < 20; ++i)
        {
            sset.insert(rname() + ' ' + rfname());
        }
        print(sset, "\n");
    }
}
