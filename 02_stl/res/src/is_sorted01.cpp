#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>
#include <vector>
#include "nutility.h"

int sumdigit(int x) 
{
    int sum{};
    while(x){
        sum += x % 10;
        x /= 10;
    }
    return sum;
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        int a[] = { 2, 5, 6, 8, 11, 16, 18, 27 };
        print(a);
        
        std::cout << "is_sorted(begin(a), end(a)) = " << is_sorted(begin(a), end(a)) << '\n';
        
        bool res2 = is_sorted(begin(a), end(a), [](int a, int b) {
            return ndigit(a) < ndigit(b);
        });
        std::cout << "res2 = " << res2 << '\n';
    }
    {
        vector<int> ivec { 11, 2, 121, 5, 333, 99, 6666, 66661, 9993};
        print(ivec);
        
        const auto f = [](int a, int b) { return sumdigit(a) < sumdigit(b); };
        cout << is_sorted(begin(ivec), end(ivec), f);
    }
    {
        vector<int> ivec { 1, 2, 5, 14, 13, 6666, 66661, 9993};
        //                              ^
        print(ivec);
        
        auto iter = is_sorted_until(ivec.begin(), ivec.end());
        std::cout << "index = " << distance(ivec.begin(), iter) << '\n';
    }
}
