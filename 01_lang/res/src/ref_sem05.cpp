#include <iostream>

int func(int x) 
{
    return x * x;
}

int main(int argc, char const *argv[])
{
    using namespace std;

    int (*fp)(int) = func;     // both are
    int (*fp_)(int) = &func;    // a pointer to function

    int(&fr)(int) = func;       // fr is a function reference
    
    std::cout << "fr(10) = " << fr(10) << '\n';
    
}
