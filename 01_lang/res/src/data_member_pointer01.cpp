#include <iostream>
#include <functional>


class Myclass{
public:
    int func(int, int);
    
    inline static int x{}, y{};
    int mx{ 34 }, my{ 235 };
};

int main(int argc, char const *argv[])
{
    int* px = &Myclass::x;
    auto py = &Myclass::y;
    
    Myclass m;
    
    int* pmx = &m.mx;
    auto pmy = &m.my;
    
    int Myclass::*pmmx = &Myclass::mx;  
    auto pmmy = &Myclass::my;
    
    std::cout << m.*pmmx << '\n';
    
    m.*pmmx = 777;
    
    std::cout << "m.mx = " << m.mx << '\n';
}
