#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "nutility.h"

class Myclass {
public:
    Myclass() = default;
    Myclass(const Myclass&) {
        std::cout << "Myclass copy ctor\n";
    }
    Myclass(Myclass&&) {
        std::cout << "Myclass move ctor\n";
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    vector<Myclass> mvec{ 10 };

    {
        auto x = *mvec.begin();             // copy ctor
        auto y = std::move(*mvec.begin());  // move ctor
    }
    std::cout << "-----------------------\n";
    {
        move_iterator<vector<Myclass>::iterator> miter{ mvec.begin() };
        auto x = *miter;        // rvalue return etti, move ctor calisti
    }
    std::cout << "-----------------------\n";
    {
        auto miter = make_move_iterator(mvec.begin());
    }
}
