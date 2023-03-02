#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> svec = { "Ankara", "Izmir", "Istanbul", "Antalya" };

        if (auto iter = std::find(svec.begin(), svec.end(), "Istanbul"); iter != svec.end()) {
            auto i = std::distance(svec.begin(), iter);
            std::cout << *iter << " degeri " << i << ".ci ogede bulundu.\n";
        }
        else {
            std::cout << "bulunamadi\n";
        }
    }
    {
        std::vector<std::string> svec;
        rfill(svec, 40, [] { return rname() + "_" + rfname(); });
        int len = 10;

        if (auto iter = std::find_if(svec.begin(), svec.end(),
            [len](const std::string &s) { return s.length() == len; }
        ); iter != svec.end()) {
            auto i = std::distance(svec.begin(), iter);
            std::cout << *iter << " degeri " << i << ".ci ogede bulundu.\n";
        }
        else {
            std::cout << "bulunamadi\n";
        }
    }
}

