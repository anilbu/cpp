#include <iostream>
#include <boost/core/demangle.hpp>

using boost::core::demangle;

template <typename T>
class Myclass {
public:
    template <typename U>
    void func(Myclass<U> p)
    {
        std::cout << "typeid(Myclass<T>) = " << demangle(typeid(Myclass<T>).name()) << '\n';
        std::cout << "typeid(p) = " << demangle(typeid(p).name()) << '\n';
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    
    Myclass<int> mint;
    Myclass<double> mdbl;
    
    mint.func(mdbl);
}
