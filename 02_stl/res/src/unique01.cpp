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
        vector<int> ivec { 1, 2, 2, 3, 5, 5, 7, 7, 7, 2, 2, 6, 6, 8, 9, 5, 3, 3, 3};
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);

        ivec.erase(unique(ivec.begin(), ivec.end()), ivec.end());

        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
    {
        vector<int> ivec { 1, 2, 2, 3, 5, 5, 7, 7, 7, 2, 2, 6, 6, 8, 9, 5, 3, 3, 3};

        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);

        ivec.erase(unique(ivec.begin(), ivec.end(), [](int a, int b) {
            return a % 2 == b % 2;
            }), ivec.end());

        std::cout << "ivec.size() = " << ivec.size() << '\n';
        print(ivec);
    }
    {
        // bosluklar teke dusurulecek
        string str{ "ali    ebubekir  neco    murat      ayse" };
        std::cout << "str = " << str << '\n';

        str.erase(unique(str.begin(), str.end(), [](char a, char b) {
            return isspace(a) && isspace(b);
        }), str.end());
        
        std::cout << "str = " << str << '\n';
    }
}
