#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;

    constexpr auto res1 = 10 <=> 5;     // res1 = strong_ordering::greater
    constexpr auto res2 = 1.0 <=> .5;   // res2 = partial_ordering::greater

    int x{}, y{ 45 };
    if (x <=> y == strong_ordering::equal)  
        std::cout << "x == y";

    if (x <=> y == strong_ordering::greater)
        std::cout << "x > y";

    if (x <=> y == strong_ordering::less)
        std::cout << "x < y";
        
    std::cout << "-------------------\n";
    
    if ((x <=> y) == 0)  
        std::cout << "x == y";

    if ((x <=> y) > 0)
        std::cout << "x > y";

    if ((x <=> y) < 0)
        std::cout << "x < y";
        
    std::cout << "-------------------\n";
    
    
}
