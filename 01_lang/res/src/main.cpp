#include <iostream>
#include <boost/core/demangle.hpp>

using boost::core::demangle;

template <typename ...Args, typename T, typename ...Args2>
void func(Args... params, T x, Args2... params2)
{
    std::cout << sizeof...(params) + sizeof...(params2) << '\n';
    std::cout << "params = " << operator<<(std::cout, demangle(typeid(params).name())...) << '\n';
    std::cout << "T = " << demangle(typeid(T).name()) << '\n';
    std::cout << "params = " << operator<<(std::cout, demangle(typeid(params2).name())...) << '\n';
    
    
    constexpr auto x = sizeof...(Args);
}



int main(int argc, char const *argv[])
{
    func(1,2,'3',4,3.14f);
    

}
