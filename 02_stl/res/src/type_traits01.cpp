#include <iostream>
#include <type_traits>
#include "nutility.h"

class Myclass {};
struct Nec {};
union Data
{
    int a : 3;
    int b : 5;
};
enum Pos { OFF, ON, HOLD };
enum class Color { Red, Green, Blue };

template <typename T>
void func(T x)
{
    // T bir tam sayi turu mu?
    constexpr bool result = std::is_integral<T>::value;

    std::cout << "is_integral<T>::value [with T = " << _demangle(typeid(T).name()) << "| = " << result << "\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;
    {

        constexpr auto b1 = is_integral<double>::value;   // b1 = false
        constexpr auto b2 = is_integral<int>::value;      // b2 = true

        constexpr auto b3 = is_pointer<int>::value;      // b3 = false
        constexpr auto b4 = is_pointer<int*>::value;     // b4 = true

        func(12);
        func(3.14);
    }
    {
        is_class<Myclass>::value;       // true
        is_class<Nec>::value;           // true
        is_class<Data>::value;          // false
        is_class<Pos>::value;           // false
        is_class<Color>::value;         // false
    }
}
