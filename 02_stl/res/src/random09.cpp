#include <iostream>
#include <random>
#include <map>
#include "nutility.h"

using MONTH_DAY = int;
using COUNT = int;

int main(int argc, char const *argv[])
{
    using namespace std;

    map<MONTH_DAY, COUNT> cmap;


    uniform_int_distribution<> dist{1, 31};
    mt19937 eng;

    for (int i = 0; i < 1'000'000; ++i)
    {
        ++cmap[dist(eng)];
    }
    
    print(cmap, "\n");
}
