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

        if (is_heap(ivec.begin(), ivec.end())) {
            std::cout << "making heap...\n";
            make_heap(ivec.begin(), ivec.end());
            print(ivec);
        }
    }
    {
        vector<int> ivec;

        rfill(ivec, 12, Irand(0, 100));
        
        make_heap(ivec.begin(), ivec.end() - 5);
        print(ivec);
        
        if(auto iter = is_heap_until(ivec.begin(), ivec.end()); iter != ivec.end()){
            std::cout << "*iter = " << *iter << '\n';
        }
    }
}