#include <iostream>

// C dilinde gelistirilmis bir modulun C++'da kullanilmasi
// #include "module.h"

extern "C" {

#include "module.h"

}

extern "C" int func(int);

int main(int argc, char const *argv[])
{
    auto x = func(20);
    std::cout << "x = " << x << '\n';

    return 0;
}
