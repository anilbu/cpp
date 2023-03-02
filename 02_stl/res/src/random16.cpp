#include <iostream>
#include <random>
#include <algorithm>
#include <iomanip>


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


    const char* pdays[] = {
        "Pazartesi", "Sali", "Carsamba", "Persembe", "Cuma", "Cumartesi", "Pazar"
    };
    
    for (auto &&p : pdays)
    {
        std::cout << p << ' ';
    }
    std::cout << "\n-------------------------------\n";
    
    
    mt19937 eng{random_device{}()};
    shuffle(begin(pdays), end(pdays), eng);
    
    for (auto &&p : pdays)
    {
        std::cout << p << ' ';
    }
    std::cout << "\n-------------------------------\n";
    
}
