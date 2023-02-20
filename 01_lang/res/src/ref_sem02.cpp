#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    int ival = 35;
    int* p = &ival;
    
    int*& rp = p;
    
    std::cout << "ival = " << ival << '\n';
    
    *rp = 99;
    
    std::cout << "ival = " << ival << '\n';
    
    int x = 29;
    rp = &x;
    
    std::cout << "*p = " << *p << '\n';
}
