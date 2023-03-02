#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> name_vec;
        rfill(name_vec, 20, rname);
        print(name_vec);

        reverse(name_vec.begin(), name_vec.end());
        // reverse(begin(name_vec), end(name_vec));

        print(name_vec);
    }
    {
        vector<string> name_vec;
        rfill(name_vec, 100, [] { return rname() + ' ' + rfname(); });

        for (auto& name : name_vec)
        {
            cout << name << '\n';
            reverse(name.begin(), name.end());
            cout << name << '\n';
            (void)getchar();
        }
    }

}
