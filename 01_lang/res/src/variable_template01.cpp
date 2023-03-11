// cppreference.com sitesinden alinmistir.

#include <iostream>
#include <type_traits>

template <typename T>
constexpr T pi = T(3.141592L);

template <typename T>
T circular_area(T r)        // function template
{
    return pi<T> * r * r;   // pi<T> is a variable template instantiation
}

int main()
{
    using namespace std;
    
    auto i = pi<double>;
    
    std::cout << "circular_area(3.96f) = " << circular_area(3.96f) << '\n';
    std::cout << "circular_area(3.96) = " << circular_area(3.96) << '\n';
    std::cout << "circular_area(3) = " << circular_area(3) << '\n';
    
}