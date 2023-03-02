#include <iostream>
#include <fstream>
#include <algorithm>
#include <iterator>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        ofstream ofs{};
    }
    {
        ofstream ofs{ "fstream01.txt", ios::out };
    }
    {
        {
            ofstream ofs{ "fstream01.txt", ios::out | ios::trunc };
            ofs << "test1\n";
        }
        (void)getchar();
        {
            ofstream ofs{ "fstream01.txt", ios::out | ios::trunc };
            ofs << "test2\n";
        }
    }
    {
        {
            ofstream ofs{ "fstream01.txt", ios::out | ios::trunc };
            ofs << "test1\n";
        }
        (void)getchar();
        {
            ofstream ofs{ "fstream01.txt", ios::out | ios::app };
            ofs << "test2\n";
        }
    }
    {
        auto ofs = create_text_file("/tmp/output.txt");
        vector<int> ivec;

        rfill(ivec, 1000, Irand{ 0, 10000 });

        // copy(ivec.begin(), ivec.end(), ostream_iterator<int>{ofs, "\n"});
        copy_if(ivec.begin(), ivec.end(), ostream_iterator<int>{ofs, "\n"}, isprime);
    }
}
