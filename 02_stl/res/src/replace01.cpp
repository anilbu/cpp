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
        vector<int> ivec { -1, 1, -2, 3, 5, -7, };
        print(ivec);
        
        replace(ivec.begin(), ivec.end(), 2, 9);    // 2'leri 9 yap
        print(ivec);

        replace_if(ivec.begin(), ivec.end(), [](int a) {    // negatifleri 0 yap
            return a < 0;
            }, 0);
        print(ivec);
    }
}
