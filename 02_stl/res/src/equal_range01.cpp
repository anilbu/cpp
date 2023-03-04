#include <iostream>
#include <iterator>
#include <set>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<int> ivec;
        rfill(ivec, 20, Irand{ 0, 5 });
        sort(ivec.begin(), ivec.end());
        print(ivec);

        int key = 4;

        auto [iter_lower, iter_upper] = equal_range(ivec.begin(), ivec.end(), key);

        cout << "index = " << distance(ivec.begin(), iter_lower) << '\n';
        if (iter_lower != ivec.end()) {
            cout << "the value at lowerbound = " << *iter_lower << '\n';
        }

        cout << "index = " << distance(ivec.begin(), iter_upper) << '\n';
        if (iter_upper != ivec.end()) {
            cout << "the value at upperbound = " << *iter_upper << '\n';
        }

        cout << "distance for equal range = " << distance(iter_lower, iter_upper) << '\n';
        print(iter_lower, iter_upper);
    }
}
