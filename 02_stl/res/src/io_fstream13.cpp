/**
 *  bir ali.exe 1000
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <numeric>
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
    auto ofs = create_text_file("/tmp/persons2.txt");
    
    ofs << ifs.rdbuf();
}
