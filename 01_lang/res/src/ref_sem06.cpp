#include <iostream>


int g = 5;

void func1(int* p) 
{
    *p = 99;
}

void func2(int& r) 
{
    r = 999;
}

int* func3()
{
    return &g;
}

int& func4()
{
    return g;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int x = 10;
    std::cout << "x = " << x << '\n';
    
    func1(&x);
    std::cout << "x = " << x << '\n';
    
    func2(x);
    std::cout << "x = " << x << '\n';
    
    int* p = func3();
    std::cout << "g = " << g << " *p = " << *p << '\n';
    *p = 10;
    std::cout << "g = " << g << " *p = " << *p << '\n';
    
    int& r = func4();
    r = 15;
    std::cout << "g = " << g << " r = " << r << '\n';
    
    func4() = 20;
    std::cout << "g = " << g << '\n';
}
