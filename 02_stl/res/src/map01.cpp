#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include "nutility.h"
#include "date.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        map<string, int> imap;

        pair<string, int> px{"ahmet", 16};
        imap.insert(px);
        print(imap);

        imap.insert(make_pair("selim", 45));
        print(imap);

        imap.insert({ "deniz", 23 });
        print(imap);

        imap.emplace("ayla", 16);
        print(imap);
    }
    {
        map<string, int> imap {
            { "ahmet", 16 },
            { "selim", 45 },
            { "deniz", 23 },
            { "ayla", 16 }
        };
        print(imap);

        imap.insert({ "selim", 99 });

        print(imap);
    }
    {
        map<string, int> imap {
            { "ahmet", 16 },
            { "selim", 45 },
            { "deniz", 23 },
            { "ayla", 16 }
        };
        print(imap);

        if (auto iter = imap.find("deniz"); iter != imap.end()) {
            iter->second += 5;
        }
        print(imap);

        string old_key = "selim";
        string new_key = "ali";
        if (auto iter = imap.find(old_key); iter != imap.end()) {
            auto value = iter->second;
            imap.erase(iter);
            value += 10;
            imap.emplace(new_key, value);
        }
        print(imap);

        old_key = "ali";
        new_key = "can";
        if (auto iter = imap.find(old_key); iter != imap.end()) {
            auto handle = imap.extract(iter);
            handle.key() = new_key;
            handle.mapped() += 10;
            imap.insert(move(handle));
        }
        print(imap);
    }
    {
        multimap<string, Date> smmap;
        rfill(smmap, 1000, [] { return make_pair(rname(), Date::random()); });

        std::cout << "smmap.size() = " << smmap.size() << '\n';

        string name = "ahmet";
        auto [beg, end] = smmap.equal_range(name);
        while (beg != end)
        {
            cout << beg->first << " " << beg->second << '\n';
            ++beg;
        }
    }
}
