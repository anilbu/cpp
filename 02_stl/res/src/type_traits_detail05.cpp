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

///////////////////////

template <typename T>
struct IsPointer : FalseType {};

template <typename T>
struct IsPointer<T*> : TrueType{};

///////////////////////

template <typename T>
void func_impl(T x, TrueType)
{
    // T turu bir pointer turu ise bu implementasyon
    std::cout << "Pointer turleri icin bu implementasyon\n";
}

template <typename T>
void func_impl(T x, FalseType)
{
    // T turu bir pointer turu degil ise bu implementasyon
    std::cout << "Pointer olmayan turler icin bu implementasyon\n";
}



template <typename T>
void func(T x)
{
    func_impl(x, typename IsPointer<T>::type{});
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int ival{};
    func(ival);
    func(&ival);
}


