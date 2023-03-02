#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
        
        ivec.resize(20);
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
    {
        vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
        
        ivec.resize(20, 99);
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
    {
        vector<int> ivec{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
        
        ivec.resize(5);
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
}
