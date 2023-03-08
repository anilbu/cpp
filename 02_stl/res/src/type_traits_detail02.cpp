#include <iostream>

template <typename T>
struct IsPointer {
    static constexpr bool value = false;
};

template <typename T>
struct IsPointer<T*> {
    static constexpr bool value = true;
};

int main(int argc, char const *argv[])
{
    constexpr auto b1 = IsPointer<int>::value;      // b1 = false
    constexpr auto b2 = IsPointer<int*>::value;     // b2 = true
}