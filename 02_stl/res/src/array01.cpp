#include <iostream>
#include <array>
#include <iterator>
#include <algorithm>
#include <string>
#include "nutility.h"
#include <cstring>  // memcpy


template<typename T, std::size_t size>
std::ostream& operator<<(std::ostream& os, const std::array<T, size>& ar)
{
    if (ar.empty())
        return os << "[]";

    os << '[';
    for (size_t i{}; i < ar.size() - 1; ++i)
        os << ar[i] << ", ";

    return os << ar.back() << ']';
}

void print_array(const int*p, size_t n)
{
    while (n--)
        printf("%d ", *p++);
}

void incr_array(int* p, size_t n)
{
    while (n--)
        ++(*p++);
}


std::array<int, 3> func(int a, int b, int c)
{
    return { a, 10 * b, 100 * c };
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        array<int, 5> arr0;                 // default initialization (with garbage values)
        array<int, 5> arr1{};               // value (zero) initialization
        array<int, 5> arr2{ 1, 3, 5, 7};    // aggregate initialization, initializer_list<int> degil
        
        array arr4{ 2, 4, 6 };   // CTAD
        
        int ar[] = {2, 4, 5, 6, 7};
        array<int, std::size(ar)> arr4;
        copy(begin(ar), end(ar), begin(arr4));
        
        memcpy(arr4.data(), ar, arr4.size() * sizeof(int));
    }
    {
        array<int, 0> arr{};
        constexpr auto size = arr.size();
        std::cout << "arr.empty() = " << arr.empty() << '\n';
        std::cout << "arr.data() = " << arr.data() << '\n';
        
        // arr[0];           // UB
        // arr.front();      // UB
        // arr.back();       // UB
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
        auto arr = func(1, 3, 5);
    }
    {
        array<int, 3> arr1 {1, 2, 3};
        auto arr2 = arr1;   // copy

        // array<int, 5> arr3 = arr1;       // sentaks hatasi
        // array<double, 3> arr4 = arr1;    // sentaks hatasi
    }
    {
        array<string, 5> arr1{ "necati", "ekrem", "akif", "coskun", "kubilay"};
        auto arr2 = std::move(arr1);

        for (const auto& s : arr1) {
            std::cout << "s.size() = " << s.size() << '\n';
        }

        print(arr1);
    }
    {
        array<int, 3> arr{2, 4, 6};
        cout << arr << '\n';
    }
    {
        array<array<int, 3>, 5> arr {
            {
                { 1, 1, 1},
                { 2, 2, 2 },
                { 3, 2, 1 },
                { 6, 2, 2 },
                { 7, 2, 4 }
            }
        };

        cout << arr << '\n';
    }
    {
        array<int, 5> arr{ 3, 7, 8, 62, 65};
        std::cout << "&arr[0] = " << &arr[0] << '\n';
        std::cout << "arr.data() = " << arr.data() << '\n';
        std::cout << "&*arr.begin() = " << &*arr.begin() << '\n';
    
        arr.front()--;
        arr.back()++;
        
        incr_array(arr.data(), arr.size());
        print_array(arr.data(), arr.size());
    }
}
