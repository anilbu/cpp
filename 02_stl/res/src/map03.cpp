#include <iostream>
#include <iomanip>
#include <map>
#include <vector>
#include <algorithm>
#include "nutility.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<string> svec;
    rfill(svec, 100'000, rtown);

    map<string, int, greater<string>> cmap;
    for (const auto& town : svec) {
        ++cmap[town];
    }
    
    vector<pair<string, int>> cvec{ cmap.begin(), cmap.end()};
    sort(cvec.begin(), cvec.end(), [](const auto& a, const auto& b) {
        return a.second > b.second;
    });

    for (const auto& [name, count] : cvec)
    {
        cout << setw(16) << name << " " << count << '\n';
    }

}
