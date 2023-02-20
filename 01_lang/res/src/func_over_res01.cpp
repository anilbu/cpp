#include <iostream>

void func(int *) 
{
    std::cout << "func(int*)\n";
}

void func(const int *) 
{
    std::cout << "func(const int*)\n";
}

int main(int argc, char const *argv[])
{
    int i = 5;
    func(&i);
    
    const int ci = 5;
    func(&ci);
}
