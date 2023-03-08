#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "nutility.h"

class Myclass {
public:
    // copy ctor (implicitly-declared ve unique_ptr kopyalanamadigi icin 
    // sentaks hatasi yerine delete edildi)
    std::unique_ptr<std::string> uptr;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        Myclass x;

        // auto y = x; // sentaks hatasi: copy ctor deleted
        auto y = std::move(x);
    }
}
