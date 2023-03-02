#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    gen_text_ifnexists("/tmp/person.txt", [](ostream& ofs) {
        ofs << left;
        for (int i = 0; i < 10; i++)
        {
            ofs << setw(16) << rname() << ' ' << setw(16) << rfname() << " " << setw(16) << rtown() << '\n';
        }
        });

    {
        auto ifs = open_text_file("/tmp/persons.txt");

        char c{};
        while (ifs.get(c)) {
            cout.put(c);
        }
    }
    {
        auto ifs = open_text_file("/tmp/persons.txt");
        string word;

        while (ifs >> word) {
            cout << word;
        }
    }
    {
        auto ifs = open_text_file("/tmp/persons.txt");
        string sline;

        while (getline(ifs, sline))
        {
            cout << sline;
        }
    }
    {
        auto ifs = open_text_file("/tmp/persons.txt");
        string sline;
        vector<string> svec;
        while (getline(ifs, sline))
        {
            svec.push_back(std::move(sline));
        }

        sort(svec.begin(), svec.end());
        copy(svec.begin(), svec.end(), ostream_iterator<string>{cout, "\n"});
    }
    {
        auto ifs = open_text_file("main.cpp");
        string sline;
        vector<string> svec;
        while (getline(ifs, sline, ';'))
        {
            cout << sline;
            // (void) getchar();
        }

        sort(svec.begin(), svec.end());
        copy(svec.begin(), svec.end(), ostream_iterator<string>{cout, "\n"});
    }
    {
        ofstream{ "/tmp/output.txt" } << "necati ergin";
    }
    {
        auto str = (ostringstream{} << hex << 5123).str();
        std::cout << "str = " << str << '\n';
    }
}
