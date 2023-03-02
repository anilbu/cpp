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

        rfill(ivec, 20, Irand{ 0, 4 });
        print(ivec);

        auto log_end = remove(ivec.begin(), ivec.end(), 2);
        std::cout << "Silinmemis ogelerin sayisi: " << std::distance(ivec.begin(), log_end) << '\n';
        print(ivec.begin(), log_end);
        std::cout << "Silinmis ogelerin sayisi: " << std::distance(log_end, ivec.end()) << '\n';
        print(log_end, ivec.end());

        std::cout << "ivec.size() = " << ivec.size() << '\n';

        std::cout << "Gercek silme islemi yapiliyor\n";
        ivec.erase(log_end, ivec.end());
        std::cout << "ivec.size() = " << ivec.size() << '\n'; // prints 20
        print(ivec);
    }
    {
        vector<string> names = { "ali", "ahmet", "mehmet", "huseyin" };
        char c = 'a';

        auto logic_end = remove_if(names.begin(), names.end(), [c](const string& s) {
            return s.find(c) != string::npos;
        });

        names.erase(logic_end, names.end());
        print(names);
    }
}
