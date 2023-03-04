#include <iostream>
#include <bitset>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        bitset<32> bx1;                     // default ctor
        bitset<16> bx2 { 0xAA55ULL };       // ULL ctor
        bitset<32> bs { "0101010101001" };  // const char* ctor
        
        std::cout << "bx = " << bx2 << '\n';
    }
}
