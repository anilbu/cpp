#include <iostream>


class Myclass {
public:
    Myclass() {
        std::cout << "Myclass()\n";
    }

    Myclass(const Myclass&) {
        std::cout << "Myclass(const Myclass&)\n";
    }

    ~Myclass() {
        std::cout << "~Myclass()\n";
    }
private:
    
};

void func(Myclass)
{
}


int main(int argc, char const *argv[])
{
    func(Myclass{});
}
