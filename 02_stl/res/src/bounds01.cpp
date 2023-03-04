#include <iostream>
#include <iterator>
#include <algorithm>
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
        auto iter_lower = lower_bound(ivec.begin(), ivec.end(), key);

        cout << "index = " << distance(ivec.begin(), iter_lower) << '\n';
        if (iter_lower != ivec.end()) {
            cout << "the value at lowerbound = " << *iter_lower << '\n';
        }

        auto iter_upper = upper_bound(ivec.begin(), ivec.end(), key);
        cout << "index = " << distance(ivec.begin(), iter_upper) << '\n';
        if (iter_upper != ivec.end()) {
            cout << "the value at upperbound = " << *iter_upper << '\n';
        }

        cout << "distance for equal range = " << distance(iter_lower, iter_upper) << '\n';
        print(iter_lower, iter_upper);
    }
    {
        vector<int> sorted_ivec;
        Irand rand{0, 10};
        for (int i = 0; i < 20; i++)
        {
            int key = rand();
            auto iter = lower_bound(sorted_ivec.begin(), sorted_ivec.end(), key);
            sorted_ivec.insert(iter, key);
            print(sorted_ivec);
            (void) getchar();
        }
        
    }
}
