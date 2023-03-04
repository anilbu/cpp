#include <iostream>
#include <iterator>
#include <set>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        multiset<int> imset = { 0, 0, 0, 0, 1, 1, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9 };

        int key = 4;

        auto iter_lower = imset.lower_bound(key);
        cout << "index = " << distance(imset.begin(), iter_lower) << '\n';
        if (iter_lower != imset.end()) {
            cout << "the value at lowerbound = " << *iter_lower << '\n';
        }

        auto iter_upper = imset.upper_bound(key);
        cout << "index = " << distance(imset.begin(), iter_upper) << '\n';
        if (iter_upper != imset.end()) {
            cout << "the value at upperbound = " << *iter_upper << '\n';
        }

        cout << "distance for equal range = " << distance(iter_lower, iter_upper) << '\n';
        print(iter_lower, iter_upper);
    }
    {
        multiset<int> imset = { 0, 0, 0, 0, 1, 1, 4, 4, 4, 5, 6, 6, 7, 7, 8, 8, 9, 9, 9, 9 };

        int key = 4;
        auto [iter_lower, iter_upper] = imset.equal_range(key);

        cout << "index = " << distance(imset.begin(), iter_lower) << '\n';
        if (iter_lower != imset.end()) {
            cout << "the value at lowerbound = " << *iter_lower << '\n';
        }

        cout << "index = " << distance(imset.begin(), iter_upper) << '\n';
        if (iter_upper != imset.end()) {
            cout << "the value at upperbound = " << *iter_upper << '\n';
        }

        cout << "distance for equal range = " << distance(iter_lower, iter_upper) << '\n';
        print(iter_lower, iter_upper);
    }
}
