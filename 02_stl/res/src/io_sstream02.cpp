#include <iostream>
#include <sstream>
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
        string str{ "123 567 912 88812 87345" };

        istringstream iss{ str };
        int sum{};

        int ival;
        while (iss >> ival) {
            cout << setw(10) << ival << "\n";
            sum += ival;
        }
        cout << "+_________\n";
        cout << setw(10) << sum << '\n';
    }
    {
        string str{ "123 567 912 88812 87345" };
        istringstream iss{ str };
        vector<int> ivec;

        int ival;
        while (iss >> ival) {
            ivec.push_back(ival);
        }

        cout << ivec.size() << " tane ogenin toplami " << accumulate(ivec.begin(), ivec.end(), 0) << '\n';
    }
    {
        string str{ "123 567 912 88812 87345" };
        istringstream iss{ str };
        vector<int> ivec{ istream_iterator<int>{iss}, {}};

        cout << ivec.size() << " tane ogenin toplami " << accumulate(ivec.begin(), ivec.end(), 0) << '\n';
    }
    {
        string str{ "123 567 912 88812 87345" };
        istringstream iss{ str };
        vector<int> ivec;

        copy_if(istream_iterator<int>{iss}, istream_iterator<int>{}, back_inserter(ivec),
            [](int x) {
                return x % 2 == 0;
            }
        );

        print(ivec);
    }
    {
        // string str{ "12/05/1987 16/02/1998" };
        // istringstream iss{ str };
        // vector<Date> dvec { istream_iterator<Date>{iss}, {}};

        string str{ "010101001 101001010 010100101 1010010 1010100101" };
        istringstream iss{ str };
        vector<bitset<16>> bvec { istream_iterator<bitset<16>>{iss}, {} };

        std::cout << "bvec.size() = " << bvec.size() << '\n';
        for (auto & bset : bvec)
        {
            std::cout << bset << " = " << bset.to_ulong() << '\n';
        }
    }
}
