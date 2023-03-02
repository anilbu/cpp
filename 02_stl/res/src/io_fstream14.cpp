#include <iostream>
#include <fstream>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    gen_text_ifnexists("/tmp/persons.txt", [](ostream& ofs) {
        ofs << left;
        for (int i = 0; i < 10; i++)
        {
            ofs << setw(16) << rname() << ' ' << setw(16) << rfname() << " " << setw(16) << rtown() << '\n';
        }
        });

    auto ifs = open_text_file("/tmp/persons.txt");
    int x{ 34 };
    
    ifs >> x;
    cout << "okuma " << (ifs ? "basarili" : "basarisiz") << '\n';
    std::cout << "ifs.eof() = " << ifs.eof() << '\n';
    
    
    
    std::cout << "x = " << x << '\n';
    // DIKKAT
    //  x degeri okunamamasina ragmen sifir degeri set edildi!

}
