#include <iostream>
#include <memory>
#include "person.h"
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    auto upx = std::make_unique<Person>("personObj");
    std::cout << "upx = " << upx << '\n';
    std::cout << "*upx = " << *upx << '\n';
    
    std::shared_ptr<Person> spx { std::move(upx) };
    std::cout << "upx = " << upx << '\n';
    std::cout << "spx = " << spx << '\n';
    std::cout << "*spx = " << *spx << '\n';
}