#include <iostream>

///////////////////////

template <typename T, T v>
struct IntegralConstant 
{
    static constexpr T value = v;
    using type = IntegralConstant;
    using value_type = T;
    
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator ()() const noexcept { return value; }
};

using FalseType = IntegralConstant<bool, false>;
using TrueType = IntegralConstant<bool, true>;

///////////////////////

template <typename T>
struct IsInteger : FalseType {};

template <>
struct IsInteger<int>: TrueType {};

template <>
struct IsInteger<unsigned int>: TrueType {};

// ...

template <>
struct IsInteger<long int>: TrueType {};

template <typename T>
constexpr bool IsInteger_v = IsInteger<T>::value;
///////////////////////

template <typename T>
struct IsPointer : FalseType {};

template <typename T>
struct IsPointer<T*> : TrueType{};

template <typename T>
constexpr bool IsPointer_v = IsPointer<T>::value;

///////////////////////

template <typename T, typename U>
struct IsSame : FalseType{};

template <typename T>
struct IsSame<T, T> : TrueType{};

template <typename T, typename U>
constexpr bool IsSame_v = IsSame<T, U>::value;

///////////////////////

int main(int argc, char const *argv[])
{
    using namespace std;
    constexpr auto b1 = IsInteger<double>::value;       // b1 = false
    constexpr auto b2 = IsInteger<int>::value;          // b2 = true
    
    constexpr auto b3 = IsPointer<int>::value;          // b3 = false
    constexpr auto b4 = IsPointer<int*>::value;         // b4 = true
    
    constexpr auto b5 = IsSame<int, double>::value;     // b5 = false
    constexpr auto b6 = IsSame<int, int>::value;        // b6 = true
}


