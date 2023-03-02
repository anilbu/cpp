#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
#include "nutility.h"

template <typename Iter>
void print_range(Iter beg, Iter end)
{
    while (beg != end)
        std::cout << *beg++ << " ";
    std::cout << "\n-----------------\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec { 12, 56, 92, 3, 57};
        auto riter = ivec.rbegin();
        cout << *riter << '\n'; // prints 57
        ++riter;
        cout << *riter << '\n'; // prints 3

        riter = ivec.rend();
        // *riter;  // UB

        auto iter = ivec.rend().base(); // iter == ivec.begin()
    }
    {
        vector<int> ivec { 12, 56, 92, 3, 57};

        auto beg = ivec.rbegin();
        auto end = ivec.rend();

        print_range(beg, end);
        print_range(end.base(), beg.base());
    }
    {
        vector<int> ivec { 12, 56, 92, 3, 57};

        if (auto iter = find(ivec.begin(), ivec.end(), 3); iter != ivec.end()) {
            cout << "Bulundu: " << *iter << '\n';
            cout << "Indeks = " << iter - ivec.begin() << '\n';
        }

        if (auto riter = find(ivec.rbegin(), ivec.rend(), 3); riter != ivec.rend()) {
            cout << "Bulundu: " << *riter << '\n';
            cout << "Indeks = " << riter - ivec.rbegin() << '\n';
        }
    }
    {
        vector<int> ivec { 12, 56, 92, 3, 57};
        
        // Bir vector'deki belirli bir degere sahip son ogeyi silin
        if (auto riter = find(ivec.rbegin(), ivec.rend(), ival); riter != ivec.rend()) {
            // ivec.erase(riter);         // sentaks hatasi: reverse_iterator parametreli bir erase fonksiyonu bulunmuyor.
            // ivec.erase(riter.base());  // yanlis: riter onceki ogeyi gosteriyor

            ivec.erase(riter.base() - 1);  // dogru
            cout << "Silme yapildi\n";
            print(ivec);
        }
        else {
            cout << "Bulunamadi\n";
        }
    }
}
