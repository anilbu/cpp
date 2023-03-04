#include <iostream>
#include <array>
#include <string>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        std::array<int, 5> arr0;
        std::array<int, 5> arr1{};               // value (zero) initialization
        std::array<int, 5> arr2{ 1, 3, 5, 7};    // aggregate initialization, initializer_list<int> degil
        std::array<int, 0> arr3{};
    }
    {
        /*
        std::array<int, 5> arr;
        int x = arr[0];  // UB cunku arr initialize edilmedi!
        */
        std::array<int, 5> arr{};
        for (auto val : arr)
            cout << val << ' '; // 0
    }
    {
        
    }
}
