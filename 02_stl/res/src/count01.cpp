#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"



int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        vector<int> ivec;
        rfill(ivec, 1000, Irand{0, 100});
        
        std::ptrdiff_t nElements = count(ivec.begin(), ivec.end(), 17);
        std::cout << "nElements = " << nElements << '\n';
    }
    {
        vector<string> svec;
        rfill(svec, 40, rtown);
        char c = 'e';
        auto nElements = count_if(svec.begin(), svec.end(), [c](const string& s){
            // return s.contains('e');  // C++20
            return s.find(c) != string::npos;
        });
        std::cout << "nElements = " << nElements << '\n';
        
    }
}
