#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include "nutility.h"

// template <typename T>
// struct Less
// {
//     bool operator()(const T &x, const T &y) const
//     {
//         return x < y;
//     }
// };

int main(int argc, char const *argv[])
{
    using namespace std;

    std::cout << "equal_to<int>{}(2,2) = " << equal_to<int>{}(2, 2) << '\n';
    std::cout << "minus<int>{}(10, 5) = " << minus<int>{}(10, 5) << '\n';
    {
        plus<int> x;
        cout << "x(10, 45) = " << x(10, 45) << '\n';
    }
    {
        string s1{ "ali" };
        string s2{ "can" };

        plus<string> x;
        cout << x(s1, s2) << '\n';
    }
    {
        vector<int> ivec{1, 6, 7, 2, 2, 3, 4, 5, 6, 2};
        list<int> ilist{1, 6, 7, 2, 2, 3, 4, 5, 6, 2};
        print(ivec);
        print(ilist);
        // transform(ivec.begin(), ivec.end(), ilist.begin(), ivec.begin(), plus<int>{});
        transform(ivec.begin(), ivec.end(), ilist.begin(), ivec.begin(), plus{});
        print(ivec);
    }
}
