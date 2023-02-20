#include <iostream>

// arguman uzerinde static_cast kullanilmadan 
// bir fonksiyon cagrisi secilebilir mi?

void f(int) {
    std::cout << "func(int)\n";
}

void f(double) {
    std::cout << "func(double)\n";
}

void f(long) {
    std::cout << "func(long)\n";
}

int main(int argc, char const *argv[])
{
    void (*func)(double) = &f;  // function pointer to f(double)
    auto f = func;              // hide f with func ptr
    
    // ...
    
    int x = 10;
    f(x);    // calls f(double)

    return 0;
}
