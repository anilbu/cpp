#include <iostream>
#include <type_traits>
#include "nutility.h"

class Myclass {};
struct Mystruct {};
union Myunion
{
    int a : 3;
    int b : 5;
};
enum Myenum { OFF, ON, HOLD };
enum class Myenumclass { Red, Green, Blue };

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
    std::cout << boolalpha;

    {
        constexpr auto b1 = is_integral<double>::value;   // b1 = false
        constexpr auto b2 = is_integral<int>::value;      // b2 = true

        constexpr auto b3 = is_pointer<int>::value;      // b3 = false
        constexpr auto b4 = is_pointer<int*>::value;     // b4 = true

        func(12);
        func(3.14);
    }
    {
        std::cout << "is_class_v<Myclass> = " << is_class_v<Myclass> << '\n';           // true
        std::cout << "is_class_v<Mystruct> = " << is_class_v<Mystruct> << '\n';         // true
        std::cout << "is_class_v<Myunion> = " << is_class_v<Myunion> << '\n';           // false
        std::cout << "is_class_v<Myenum> = " << is_class_v<Myenum> << '\n';             // false
        std::cout << "is_class_v<Myenumclass> = " << is_class_v<Myenumclass> << '\n';   // false
    }
}
