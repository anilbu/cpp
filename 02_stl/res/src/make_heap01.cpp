#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec;

        rfill(ivec, 12, Irand(0, 100));
        print(ivec);

        make_heap(ivec.begin(), ivec.end());
        print(ivec);
    }
}


/*
21 35 62 84 74 27 41 98 13 89 14 85
-----------------------------------------------------------------------------
98 89 85 84 74 62 41 35 13 21 14 27
-----------------------------------------------------------------------------
                       98
               89              85
           84      74      62      41
         35  13  21  14  27
*/