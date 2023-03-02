#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec { -1, 1, -2, 3, 5, -7, };
        print(ivec);
        {
            vector<int> dest_vec;
            replace_copy(ivec.begin(), ivec.end(), back_inserter(dest_vec), 2, 9);    // 2'leri 9 yap
            print(ivec);
            print(dest_vec);
        }
        {
            vector<int> dest_vec;
            replace_copy_if(ivec.begin(), ivec.end(), back_inserter(dest_vec), [](int a) {    // negatifleri 0 yap
                return a < 0;
                }, 0);
            print(ivec);
            print(dest_vec);
        }
    }
}
