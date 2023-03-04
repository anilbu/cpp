#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        map<string, int> imap {
            { "ahmet", 16 },
            { "selim", 45 },
            { "deniz", 23 },
            { "ayla", 16 }
        };

        for (auto iter = imap.begin(); iter != imap.end(); ++iter)
        {
            const auto& key = iter->first;
            auto& value = iter->second;
            cout << key << " " << value << '\n';
        }

        for (const auto& [key, val] : imap) {
            std::cout << key << " " << val << "\n";
        }
    }
    {
        map<string, int> imap {
            { "ahmet", 16 },
            { "selim", 45 },
            { "deniz", 23 },
            { "ayla", 16 }
        };
        print(imap);
        
        if(auto iter = imap.find("ahmet"); iter != imap.end()) {
            std::cout << "iter->first = " << iter->first << '\n';
            std::cout << "iter->second = " << iter->second << '\n';
        }
    }
    {
        map<string, int> imap {
            { "ahmet", 16 },
            { "selim", 45 },
            { "deniz", 23 },
            { "ayla", 16 }
        };
        print(imap);
        
        imap.insert({"selim", 99});
        
        print(imap);
    }
}
