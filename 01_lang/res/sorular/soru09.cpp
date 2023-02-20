#include <iostream>

/*
    Programin ciktisi nedir?
*/


void bar(int &) {
    std::cout << 3;
}
void bar(int &&) {
    std::cout << 4;
}

void func(int &x) {
    std::cout << 1;
    bar(x);
}
void func(int &&x) {
    std::cout << 1;
    bar(x);
}

int main(int argc, char const *argv[])
{
    func(10);
}
