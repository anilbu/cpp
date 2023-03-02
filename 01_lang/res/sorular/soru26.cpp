#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include "nutility.h"

// Verilen bir vector<string> nesnesi icin
//      uzunlugu 4 olanlar silenecek
//      uzunlugu 5 olanlardan bir tane daha eklenecek
//      digerlerinde degisiklik yapilamayacak
// bir fonksiyon yazin
void process(/* ... */)
{

}

int main(int argc, char const *argv[])
{
    using namespace std;
    auto print = [](const auto& cont) {
        for (auto iter = cont.begin(); iter < cont.end(); ++iter)
        {
            std::cout << *iter << " ";
        }

        std::cout << "\n-------------\n";
    };
    vector<string> svec;

    rfill(svec, 30, rname);
    print(svec);

    process(svec);
    print(svec);

}












































void cevap1(std::vector<std::string>& svec)
{
    for (auto iter = svec.begin(); iter < svec.end(); )
    {
        if (iter->size() == 4)
        {
            iter = svec.erase(iter);
        }
        else if (iter->size() == 5)
        {
            iter = svec.insert(iter, *iter);    // iter invalidate olmus olabilir
            advance(iter, 2);   // islenen + yeni eklenen
        }
        else {
            ++iter; // atla
        }
    }
}

void cevap2(std::vector<std::string>& svec)
{
    using namespace std;

    vector<string> tmp{};
    tmp.reserve(svec.size());
    for (const auto &elem : svec)
    {
        if (elem.size() == 4)
            continue;
        if (elem.size() == 5)
            tmp.push_back(elem);

        tmp.push_back(elem);
    }

    svec.swap(tmp);
}
