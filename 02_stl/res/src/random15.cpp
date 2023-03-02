#include <iostream>
#include <random>
#include <map>
#include <iomanip>
#include <string>
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

    mt19937 eng;

    const char * const pdays[] = {
        "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"
    };

    const double probs[] = {
        100., 100., 120., 100., 120., 80., 80. };

    discrete_distribution<int> dist {std::begin(probs), std::end(probs)};
    map<int, int> hist;
    
    for (int i = 0; i < 10'000'000; ++i)
    {
        ++hist[dist(eng)];
    }
    
    print_histogram(hist, 100000);
}
