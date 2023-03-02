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
        istringstream iss{ "0123456789BABADEDE" };
        char c;
        while (iss.get(c))       // while((c = iss.get()) != EOF)
        {
            cout << c << " " << static_cast<int>(c) << '\n';
        }
    }
    {
        cout << "tam sayilar giriniz: ";
        string line{};
        getline(cin, line);
        
        istringstream iss {line};
        vector<int> ivec {istream_iterator<int>{iss}, {}};
        
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        sort(ivec.begin(), ivec.end(), greater{});
        copy(ivec.begin(), ivec.end(), ostream_iterator<int>{cout, ", "});
    }
}
