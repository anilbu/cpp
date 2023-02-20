#include <iostream>

int g;

int main() {
    constexpr int* p = &g;            // p = int* const
    constexpr const int* p = &g;      // p = const int* const

    constexpr int prime_digits[] = { 2, 3, 5, 7 };
    constexpr auto val = prime_digits[3];
}
