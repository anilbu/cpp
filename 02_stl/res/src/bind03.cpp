#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
#include <iterator>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::placeholders;

    vector<int> ivec;
    Irand rand{ 0, 10 };
    rfill(ivec, 10, rand);
    print(ivec);
    
    copy_if(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "}, 
        [](int x) {
            return x > 5;
        }
    );
    std::cout << "\n-------------------\n";
    
    copy_if(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, " "}, 
        bind(greater{}, _1, 5)
    );
    std::cout << "\n-------------------\n";
}