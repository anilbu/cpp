#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<int> ivec;

        rfill(ivec, 10, Irand{ 0, 99 });
        print(ivec);

        sort(ivec.begin(), ivec.end());             // less
        print(ivec);

        sort(ivec.begin(), ivec.end(), greater{});  // greater
        print(ivec);
    }
    {
        vector<string> svec;

        rfill(svec, 20, rname);
        print(svec);

        sort(svec.begin(), svec.end());
        print(svec);

        sort(svec.rbegin(), svec.rend());
        print(svec);

        sort(svec.begin(), svec.end(), greater{});
        print(svec);

        auto sort_criteria = [](const string& a, const string& b) {
            return a.length() < b.length() ||
                   a.length() == b.length() && a < b;
        };
        sort(svec.begin(), svec.end(), sort_criteria);
        print(svec);
    }
    {
        
    }
}
