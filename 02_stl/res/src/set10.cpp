#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<int> x {1, 3, 5, 7, 9};
        set<int> y {0, 2, 4, 6, 8};
        
        std::cout << "x.size() = " << x.size() << '\n';
        print(x);
        std::cout << "y.size() = " << y.size() << '\n';
        print(y);
        
        x.merge(y);
        
        std::cout << "x.size() = " << x.size() << '\n';
        print(x);
        std::cout << "y.size() = " << y.size() << '\n';
        print(y);
        
    }
}
