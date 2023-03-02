#include <iostream>
#include <bitset>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    std::cout << "ios::basefield = " << bitset<32>(ios::basefield) << '\n';
    std::cout << "ios::hex       = " << bitset<32>(ios::hex) << '\n';
    std::cout << "ios::oct       = " << bitset<32>(ios::oct) << '\n';
    std::cout << "ios::dec       = " << bitset<32>(ios::dec) << '\n';
}
