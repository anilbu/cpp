#include <iostream>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <iterator>
#include <algorithm>
#include <numeric>
#include <bitset>
#include "nutility.h"
#include "date.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        ofstream ofs{ "/tmp/numbers.txt" };
        if (!ofs) {
            cerr << "Dosya acilamadi\n";
            return 1;
        }
        
        for (int i = 0; i < 1000; ++i)
        {
            ofs << i << '\n';
        }
    }
    {
        ifstream ifs{ "/tmp/numbers.txt" };
        if (!ifs) {
            cerr << "Dosya acilamadi\n";
            return 2;
        }

        vector<int> ivec { istream_iterator<int>{ifs}, istream_iterator<int>{}};

        std::cout << "ivec.size() = " << ivec.size() << '\n';
    }
}
