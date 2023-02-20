#include <iostream>

int func(int x)
try
{
    std::cout << "func basladi x = " << x << '\n';
    if(x > 10)
        throw 3.14;
    if(x > 0)
        throw 1;
        
    std::cout << "func bitiyor\n";
    return 1;
}
catch(int)
{
    std::cerr << "Hata yakalandi: int\n";
    std::cerr << "param x = " << x << '\n';
    return -1;
}
catch(double)
{
    std::cerr << "Hata yakalandi: double\n";
    std::cerr << "param x = " << x << '\n';
    return -2;
}


int main(int argc, char const *argv[])
{
    int retval;
    retval = func(0);
    std::cout << "retval = " << retval << '\n';
    
    retval = func(1);
    std::cout << "retval = " << retval << '\n';
    
    retval = func(14);
    std::cout << "retval = " << retval << '\n';
    
}