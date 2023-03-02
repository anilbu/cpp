#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include "nutility.h"

// finding the median of a range:
template <typename T>
T median(std::vector<T> vec) {
    std::nth_element(vec.begin(), vec.begin() + (vec.size() / 2), vec.end());
    return vec[vec.size() / 2];
}

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec;
        rfill(ivec, 10, Irand{ 0, 50 });
        print(ivec);
        
        auto mid_iter = ivec.begin() + 5;
        std::cout << "*mid_iter = " << *mid_iter << '\n';
        std::nth_element(ivec.begin(), mid_iter, ivec.end());
        std::cout << "*mid_iter = " << *mid_iter << '\n';
        print(ivec);
    }
    {
        vector<int> ivec;
        rfill(ivec, 10, Irand{ 0, 50 });
        std::cout << "median(ivec) = " << median(ivec) << '\n';
        print(ivec);
    }
}
