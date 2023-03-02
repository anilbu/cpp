#include <iostream>
#include <random>
using namespace std;

void print_random() 
{
    mt19937 eng{ 78324873u };
    for (int i = 0; i < 5; i++)
    {
        cout << eng() << '\n';
    }
}

void print_dist() 
{
    mt19937 eng{ 78324873u };
    uniform_int_distribution dist{17912, 18907};
    
    for (int i = 0; i < 5; i++)
    {
        cout << dist(eng) << '\n';
    }
}

int main(int argc, char const *argv[])
{
    print_random();
    std::cout << "---------------\n";
    print_random();
    std::cout << "---------------\n";
    print_dist();
    std::cout << "---------------\n";
    print_dist();
}
