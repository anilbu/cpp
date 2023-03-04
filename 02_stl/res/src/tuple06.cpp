#include <iostream>
#include <tuple>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        int x = 10;
        int y = 20;
        int z = 30;
        
        int temp = x;
        x = y;
        y = z;
        z = temp;
        
        std::cout << "x = " << x << '\n';
        std::cout << "y = " << y << '\n';
        std::cout << "z = " << z << '\n';
    }
    {
        int x = 10;
        int y = 20;
        int z = 30;
        
        tie(x, y, z) = tie(y, z, x);
        
        std::cout << "x = " << x << '\n';
        std::cout << "y = " << y << '\n';
        std::cout << "z = " << z << '\n';
    }
}
