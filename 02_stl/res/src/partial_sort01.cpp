#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<string> svec;

        rfill(svec, 10, rname);
        print(svec);

        partial_sort(svec.begin(), svec.begin() + 5, svec.end());
        print(svec);

        partial_sort(svec.begin(), svec.begin() + 5, svec.end(), greater{});
        print(svec);

        partial_sort(svec.begin(), svec.begin() + 5, svec.end(), [](const auto& a, const auto& b) {
            return count(a.begin(), a.end(), 'a') > count(b.begin(), b.end(), 'a');
        });
        print(svec);
    }
}
