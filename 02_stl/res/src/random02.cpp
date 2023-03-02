#include <iostream>
#include <random>

int main(int argc, char const *argv[])
{
    using namespace std;
    std::cout << "sizeof(mt19937) = " << sizeof(mt19937) << '\n';
    std::cout << "sizeof(knuth_b) = " << sizeof(knuth_b) << '\n';
    std::cout << "sizeof(ranlux24) = " << sizeof(ranlux24) << '\n';
}
