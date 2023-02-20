#include <iostream>

class Myclass{};

// (1)
void func(Myclass&)
{
    std::cout << "lvalue ref\n";
}

// (2)
void func(const Myclass&)
{
    std::cout << "const lvalue ref\n";
}

// (3)
void func(Myclass&&)
{
    std::cout << "rvalue ref\n";
}

void call_func(Myclass& x)
{
    func(x);
}

void call_func(const Myclass& x)
{
    func(x);
}

void call_func(Myclass&& x)
{
    func(std::move(x));    // x parametresi rvalue ref ancak lvalue kategorisinde
}

int main(int argc, char const *argv[])
{
    using namespace std;

    Myclass m;
    const Myclass cm;

    // (1)
    func(m);
    call_func(m);
    
    std::cout << "----------------\n";

    // (2)
    func(cm);
    call_func(cm);
    
    std::cout << "----------------\n";

    // (3)
    func(Myclass{});
    call_func(Myclass{});
}
