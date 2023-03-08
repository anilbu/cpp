#include <iostream>
#include <memory>

class Deleter {
public:
    void operator() (const std::string* p)
    {
        std::cout << "deleting " << p << "...\n";
        delete p;
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        unique_ptr<string, Deleter> uptr1{ new std::string{ "necati ergin" } };
    }
    std::cout << "------------------------\n";
    {
        auto fdel = [](const string* p) {
            std::cout << "deleting " << p << "...\n";
            delete p;
        };

        unique_ptr<string, decltype(fdel)> uptr2{ new std::string{ "necati ergin" } };
    }
}