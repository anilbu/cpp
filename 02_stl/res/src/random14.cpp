#include <iostream>
#include <random>
#include <map>
#include <iomanip>
#include <string>
#include "nutility.h"

template<typename C>
void print_histogram(const C& c, int per_count = 10000)
{
    for (auto [value, count] : c)
    {
        std::cout << std::setw(2) << value << " " << std::string(count/per_count, '*') << '\n';
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    mt19937 eng;
    discrete_distribution dist{0, 10, 10, 10, 10, 10, 11.76};
    
    map<int, int> histogram;
    for (size_t i = 0; i < 1'000'000; i++)
    {
        ++histogram[dist(eng)];
    }
    
    print_histogram(histogram);
}
