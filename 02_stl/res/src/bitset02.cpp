#include <iostream>
#include <bitset>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        bitset<8> bs {0};
        std::cout << "bs = " << bs << '\n';
        
        bs.set(4);
        std::cout << "bs.set(4)   bs = " << bs << '\n';

        bs.set();
        std::cout << "bs.set( )   bs = " << bs << '\n';
    }
    {
        bitset<8> bs { 0xFFFFFFFFUL };
        
        std::cout << "bs = " << bs << '\n';
        bs.reset(4);
        std::cout << "bs.reset(4) bs = " << bs << '\n';

        bs.reset();
        std::cout << "bs.reset( ) bs = " << bs << '\n';
    }
    {
        bitset<8> bs { 0xFFUL };
        
        std::cout << "bs = " << bs << '\n';
        bs.reset().set(4);
        std::cout << "bs.reset().set(4)\n";
        std::cout << "bs = " << bs << '\n';
    }
    {
        bitset<8> bs { 0xF0L };

        std::cout << "bs = " << bs << " bs.test(2) = " << bs.test(2) << '\n';
        std::cout << "bs = " << bs << " bs.test(6) = " << bs.test(6) << '\n';
    }
    {
        bitset<8> bs { 0x0FUL };
        
        std::cout << "bs = " << bs << " bs.all() = " << bs.all() << '\n';
        bs.reset(3);
        std::cout << "bs = " << bs << " bs.all() = " << bs.all() << '\n';
    }
    {
        bitset<8> bs { 0 };
        
        std::cout << "bs = " << bs << " bs.any() = " << bs.any() << '\n';
        bs.set(3);
        std::cout << "bs = " << bs << " bs.any() = " << bs.any() << '\n';
    }
    {
        bitset<8> bs { 0 };
        
        std::cout << "bs = " << bs << " bs.none() = " << bs.none() << '\n';
        bs.set(3);
        std::cout << "bs = " << bs << " bs.none() = " << bs.none() << '\n';
    }
    {
        bitset<8> bs { 0xF0 };

        std::cout << "            bs = " << bs << '\n';
        bs.flip();
        std::cout << "bs.flip( )  bs = " << bs << '\n';
        bs.flip(6);
        std::cout << "bs.flip(6)  bs = " << bs << '\n';
    }
    {
        bitset<8> bs { 0xF0 };
        std::cout << "bs = " << bs << '\n';
        std::cout << "~bs = " << ~bs << '\n';
    }
    {
        bitset<8> bs1 {0xF3};
        bitset<8> bs2 {0x03};
        
        std::cout << "bs1 = " << bs1 << '\n';
        std::cout << "bs2 = " << bs2 << '\n';
        std::cout << "(bs1 & bs2) = " << (bs1 & bs2) << '\n';
        std::cout << "(bs1 | bs2) = " << (bs1 | bs2) << '\n';
        std::cout << "(bs1 ^ bs2) = " << (bs1 ^ bs2) << '\n';
        
    }
}
