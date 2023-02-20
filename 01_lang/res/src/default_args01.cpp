#include <iostream>

int g = 20;

void func(int x = g++);

int main() {
    func();
    func();
    func();

    std::cout << "g = " << g << '\n';
}

void func(int x) {
    std::cout << "x = " << x << '\n';
}
