#include <iostream>
#include <fstream>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        auto ofs = create_text_file("/tmp/output.txt");
        for (int i = 0; i < 100; i++)
        {
            ofs << i << '\n';
        }
    }
    {
        auto ifs = ifstream("/tmp/output.txt");
        std::cout << "ifs.tellg() = " << ifs.tellg() << '\n';
        
    }
    {
        auto ifs = ifstream("/tmp/output.txt", ios::ate);
        std::cout << "ifs.tellg() = " << ifs.tellg() << '\n';
    }
}
