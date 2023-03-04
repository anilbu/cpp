#include <iostream>
#include <string>
#include <set>
#include <iterator>
#include <algorithm>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<string> sset { "ali", "ayse", "tarken", "tekin", "yelda" };
        print(sset);

        if (auto [iter, success] = sset.insert("mehmet"); success) {
            std::cout << "Ekleme islemi yapildi\n";
            std::cout << "*iter = " << *iter << '\n';
        }
        else {
            std::cout << "Oge zaten set'de var\n";
            std::cout << "*iter = " << *iter << '\n';
        }

        if (auto [iter, success] = sset.insert("mehmet"); success) {
            std::cout << "Ekleme islemi yapildi\n";
            std::cout << "*iter = " << *iter << '\n';
        }
        else {
            std::cout << "Oge zaten set'de var\n";
            std::cout << "*iter = " << *iter << '\n';
        }
    }
    {
        set<int> iset{ 1, 3, 5, 7, 11, 13};
        print(iset);
        if (auto iter = iset.find(7); iter != iset.end()) {
            // hint insert:
            iset.insert(iter, 9);
            print(iset);
        }
    }
    {
        set<int> iset;
        
        vector<int> ivec;
        rfill(ivec, 20, Irand{0, 1000});
        print(ivec);
        
        copy(ivec.begin(), ivec.end(), inserter(iset, iset.begin()));
        print(iset);
    }
}
