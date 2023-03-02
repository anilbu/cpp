#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include "nutility.h"

template <typename RanIt>
void heap_sort(RanIt beg, RanIt end) {
    std::make_heap(beg, end);
    std::sort_heap(beg, end);
}

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec;

        rfill(ivec, 12, Irand(0, 100));
        print(ivec);

        make_heap(ivec.begin(), ivec.end());
        print(ivec);

        sort_heap(ivec.begin(), ivec.end());
        print(ivec);
    }
}
