#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "nutility.h"

using namespace std;

int main(int argc, char const *argv[])
{
    set<int> x{1, 5, 7, 9, 12};
    set<int> y{2, 4, 8, 9, 12};
    set<int> z{4, 8, 9};
    vector<int> ivec;
    
    
    auto isSubset = includes(y.begin(), y.end(), z.begin(), z.end());
    std::cout << "isSubset = " << isSubset << '\n';
    
    /// x n y
    set_intersection(x.begin(), x.end(), y.begin(), y.end(), back_inserter(ivec));
    print(ivec);
    ivec.clear();

    // x u y
    set_union(x.begin(), x.end(), y.begin(), y.end(), back_inserter(ivec));
    print(ivec);
    ivec.clear();
    
    // x - y
    set_difference(x.begin(), x.end(), y.begin(), y.end(), back_inserter(ivec));
    print(ivec);
    ivec.clear();
    
    // y - x
    set_difference(y.begin(), y.end(), x.begin(), x.end(), back_inserter(ivec));
    print(ivec);
    ivec.clear();
    
    // (x u b) - (x n y)
    set_symmetric_difference(x.begin(), x.end(), y.begin(), y.end(), back_inserter(ivec));
    print(ivec);
}
