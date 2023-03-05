#include <iostream>
#include <functional>


struct Candle {
    double m_open{};
    double m_high{};
    double m_low{};
    double m_close{};
};

void func(Candle x, double Candle::*p) {
    std::cout << x.*p << '\n';
}

int main(int argc, char const *argv[])
{
    Candle x;
    func(x, &Candle::m_open);
    
    auto mp = &Candle::m_high;
    func(x, mp);
    
    std::invoke(mp, x) = 67;
}
