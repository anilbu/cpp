#include <iostream>

int foo()
{
    std::cout << "foo()\n";
    return 5;
}

void func()
{
    static int x = foo();
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    std::cout << "main basladi\n";
    
    func();
    func();
    func();
    
    std::cout << "main bitiyor\n";
}
