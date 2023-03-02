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
    
    vector<int> ivec;
    Irand rand{10, 99};
    for (int i = 0; i < 20; i++)
    {
        int ival = rand();
        std::cout << "ival = " << ival << '\n';
        ivec.push_back(ival);
        push_heap(ivec.begin(), ivec.end());
        print(ivec);
        (void) getchar();
    }
    
}
