#include <iostream>
#include <functional>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        int x = 10;
        reference_wrapper<int> r1{ x };
        reference_wrapper r2 = x;            // CTAD
        auto r3 = ref(x);
    }
    {
        int x = 10;
        auto r = ref(x);
        
        std::cout << "r = " << r << '\n';
        std::cout << "r.operator int&() = " << r.operator int&() << '\n';
    }
}
