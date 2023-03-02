#include <iostream>
#include <random>
#include <map>
#include <iomanip>
#include <string>
#include "nutility.h"

template<typename C>
void print_histogram(const C& c)
{
    for (auto [value, count] : c)
    {
        std::cout << std::setw(2) << value << " " << std::string(count/2000, '*') << '\n';
    }
    
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    mt19937 eng;
    normal_distribution<double> dist{100, 5};
    
    map<int, int> histogram;
    for (size_t i = 0; i < 1'000'000; i++)
    {
        ++histogram[static_cast<int>(round(dist(eng)))];
    }
    
    print_histogram(histogram);
}
