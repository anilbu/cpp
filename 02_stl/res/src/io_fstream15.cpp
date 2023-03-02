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
    ifs.exceptions(ios::failbit | ios::eofbit | ios::badbit);

    try {

        int x{ 34 };
        ifs >> x;
    }
    catch(const std::ios_base::failure& ex) {
        std::cout << "ex.what() = " << ex.what() << '\n';
        
    }
}
