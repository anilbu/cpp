#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec { 1, 3, 5, 7, 9};

        print(ivec);
        ivec.front() = 100;
        ivec.back() += 11;
        print(ivec);
    }
}
