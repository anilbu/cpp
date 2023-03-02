#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <iomanip>
#include "nutility.h"

template<typename C>
void print_histogram(const C& c, int per_count = 1000)
{
    for (auto [value, count] : c)
    {
        std::cout << std::setw(2) << value << ": " << std::setw(8) << count << ' ' << std::string(count / per_count, '*') << '\n';
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    vector<string> svec;
    rfill(svec, 100, rname);
    
    sort(svec.begin(), svec.end());
    unique(svec.begin(), svec.end());
    shuffle(svec.begin(), svec.end(), mt19937{});
    
    print(svec);
}
