#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<int> ivec { 1, 3, 5, 7, 9};
        auto iter1 = ivec.begin();
        auto iter2 = ivec.end() - 1;
        print(ivec);

        swap(*iter1, *iter2);
        print(ivec);
    }
    {
        vector<int> ivec { 1, 3, 5, 7, 9};
        auto iter1 = ivec.begin();
        auto iter2 = ivec.end() - 1;
        print(ivec);

        iter_swap(iter1, iter2);
        print(ivec);
    }
    {
        int a[] = { 1, 3, 5, 7, 9 };
        print(a);
        iter_swap(begin(a), end(a) - 1);
        print(a);
    }
    {
        list<int> ilst {0, 9, 4, 6, 8};
        vector<int> ivec {1, 3, 5, 7, 2};

        iter_swap(next(ilst.begin()), prev(ivec.end()));

        print(ivec);    // prints 0 2 4 6 8
        print(ilst);    // prints 1 3 5 7 9
    }
}
