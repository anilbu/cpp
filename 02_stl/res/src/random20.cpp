#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    mt19937 eng{ random_device{}() };
    uniform_int_distribution dist{ 1000, 1200 };
    
    std::cout << "random_device{}.entropy() = " << random_device{}.entropy() << '\n';
    
}
