#include <iostream>
#include <string>
#include <set>
#include <utility>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<string> sset = { "ayse", "fatma", "necati", "ilker", "coskun", "emin" };
        print(sset);

        string old_key = "ayse";
        string new_key = "zeliha";

        // key set'ten cikarildi ancak oge yada ogeyi tutan node destroy edilmedi
        if (auto handle = sset.extract(old_key); handle) {
            handle.value() = new_key;
            sset.insert(std::move(handle));
        }

        print(sset);
    }
    {
        set<string> sset = { "ayse", "fatma", "necati", "ilker", "coskun", "emin" };

        string old_key = "ayse";
        string new_key = "zeliha";

        if (auto iter = sset.find(old_key); iter != sset.end())
        {
            auto handle = sset.extract(iter);
            // handle = std::set<std::string>::node_type
            handle.value() = new_key;
            sset.insert(std::move(handle));
        }
        print(sset);
    }
    {
        // C++17 oncesinde kullanilan yontem:
        set<string> sset { "ayse", "fatma", "necati", "ilker", "coskun", "emin" };
        string old_key = "ayse";
        string new_key = "zeliha";

        if (auto iter = sset.find(old_key); iter != sset.end())
        {
            sset.erase(iter);
            sset.insert(new_key);
        }
        print(sset);
    }
}
