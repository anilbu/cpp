#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;

    typedef int* iptr;

    int x = 5;
    int y = 45;

    const iptr p = &x;
    // p = &y;  // [1]
    *p = 99; // [2]
}









































    // cevap: typedef ptr oldugunda her zaman top level const
    // [1] gecersiz, [2] gecerli
