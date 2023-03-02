#include <iostream>
#include <vector>
#include <list>
#include <iterator>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    vector<int> ivec{ 23, 13, 22, 3, 1, 5, 6, 33, 2};
    list<int> ilist{ 23, 13, 22, 3, 1, 5, 6, 33, 2};
    
    {
        auto iter = ivec.begin();
        std::cout << "*iter = " << *iter << '\n';

        advance(iter, 3);
        std::cout << "*iter = " << *iter << '\n';
    }
    {
        auto iter = ivec.end();

        advance(iter, -3);
        std::cout << "*iter = " << *iter << '\n';
    }
}
