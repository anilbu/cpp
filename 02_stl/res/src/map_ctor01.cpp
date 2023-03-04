#include <iostream>
#include <map>
#include <vector>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        {
            map<string, int> imap;
            map<string, int, greater<string>> imap_greater;
        }
        {
            map<string, int> imap {
                { "ahmet", 16 },
                { "selim", 45 },
                { "deniz", 23 },
                { "ayla", 16 }
            };
            
            print(imap);
        }
        {
            vector<pair<string, int>> ivec;
            Irand rand{ 0, 200 };
            rfill(ivec, 20, [&rand] { return pair{ rname(), rand() }; });
            print(ivec);

            map<string, int> imap(ivec.begin(), ivec.end());
            print(imap);
        }
    }
}
