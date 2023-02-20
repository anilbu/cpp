#include <iostream>
#include <string>

class Myclass
{
public:
    Myclass() {
        std::cout << "Myclass() this = " << this << '\n';
    }

    Myclass(int a, int b) {
        std::cout << "Myclass(int a, int b) a = " << a << " b = " << b << '\n';
    }

    ~Myclass() {
        std::cout << "~Myclass() this = " << this << '\n';
    }

    void foo() {
        std::cout << "Myclass::foo() this = " << this << '\n';
    }
};

void func(const Myclass &)
{
    std::cout << "func(const Myclass&)\n";
}

void func(Myclass &&)
{
    std::cout << "func(Myclass&&)\n";
}

int main(int argc, char const *argv[])
{
    {
        func(Myclass{});
    }

    std::cout << "=====================\n";

    {
        std::cout << "main basliyor\n";
        Myclass().foo();
        std::cout << "main devam ediyor\n";
    }

    std::cout << "=====================\n";

    {
        std::cout << "[1] main basliyor\n";
        if (1)
        {
            Myclass &&r = Myclass{3, 5};
            std::cout << "[2] main devam ediyor\n";
            r.foo(); // life extension
        }

        std::cout << "[3] main devam ediyor\n";
    }
}
