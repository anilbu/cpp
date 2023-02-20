#include <iostream>

constexpr int sum_square(int a, int b) {
    return a * a + b * b;
}

constexpr int ndigit(int x) {
    int digit_cnt = 0;

    if (x == 0)
        return 1;

    while (x) {
        ++digit_cnt;
        x /= 10;
    }
    return digit_cnt;
}

int main() {
    const int a = 123;  // a'nin olusturdugu ifade: sabit ifadesi
    const int b = 456;

    constexpr auto val1 = sum_square(10, 20);    // constexpr
    constexpr auto val2 = ndigit(a + b);  // gecerli
    constexpr auto val3 = sum_square(ndigit(a), ndigit(b));  // gecerli
}
