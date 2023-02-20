#include <iostream>

template <typename T>
class Myclass {
public:
    inline static int x {0};
    
    void func(){
        ++x;
    }
};

int main(int argc, char const *argv[])
{
    Myclass <int> m1;
    Myclass <double> m2;
    Myclass <char> m3;
    
    std::cout << m1.x << m2.x << m3.x << '\n';
    m2.func();
    std::cout << m1.x << m2.x << m3.x << '\n';
    m2.func();
    std::cout << m1.x << m2.x << m3.x << '\n';
}
