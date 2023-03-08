#include <iostream>
#include <string>
#include <memory>

class Myclass {
public:
    Myclass() = default;

    Myclass(const Myclass& other)
        : uptr{ other.uptr ? new std::string{*other.uptr.get()} : nullptr }
    {
        std::cout << "Myclass copy ctor\n";
    }

    Myclass(Myclass&&): uptr{ std::move(uptr) }
    {
        std::cout << "Myclass move ctor\n";
    }

private:
    std::unique_ptr<std::string> uptr{};
};

int main(int argc, char const *argv[])
{
    using namespace std;

    Myclass x;
    auto y = x;
    auto z = std::move(x);
}
