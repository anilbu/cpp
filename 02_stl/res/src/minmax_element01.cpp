#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {


        vector<string> names;
        rfill(names, 100, []
            { return rname() + ' ' + rfname(); });

        auto iter = max_element(names.begin(), names.end());
        cout << *iter << '\n';

        cout << *min_element(names.begin(), names.end()) << '\n';
        cout << *max_element(names.begin(), names.end()) << '\n';

        cout << min_element(names.begin(), names.end())->length() << '\n';
        cout << max_element(names.begin(), names.end())->length() << '\n';

        // pair<vector<string>::iterator, vector<string>::iterator> result;
        auto p = minmax_element(names.begin(), names.end());
        cout << "min = " << *p.first << " max = " << *p.second << '\n';

        cout << *minmax_element(names.begin(), names.end()).first << '\n';
        cout << *minmax_element(names.begin(), names.end()).second << '\n';

        // structured binding
        auto [min_iter, max_iter] = minmax_element(names.begin(), names.end());
        cout << *min_iter << '\n';
        cout << *max_iter << '\n';

        cout << *min_element(names.begin(), names.end(),
            [](const string& a, const string& b) {
                return a.size() < b.size();
            }
        ) << '\n';
    }
    {
        vector<int> ivec;
        rfill(ivec, 100, Irand{ -10000, 10000 });
        cout << *min_element(ivec.begin(), ivec.end()) << '\n';
        cout << *min_element(ivec.begin(), ivec.end(),
            [](const int a, const int b) {
                return abs(a) < abs(b);
            }
        ) << '\n';
    }
}
