#include <iostream>
#include <type_traits>

template <typename T>
void func(T x)
{
    if(std::is_pointer_v<T>) {
        std::cout << "T is a pointer type\n";
    }
    else {
        std::cout << "T is not a pointer type\n";
    }
}

template <typename T>
void foo(T x)
{
    if constexpr (std::is_integral_v<T>) {
        ++x;
    }
}

/// Eger T bir pointer ise gosterdigi nesnenin degerini, degilse kendi degerini dondursun:
template <typename T>
std::remove_pointer_t<T> get_value(T x)
{
    if constexpr(std::is_pointer_v<T>)
        return *x;
    else
        return x;
}

class Myclass { };

int main(int argc, char const *argv[])
{
    int ival{};
    func(ival);
    func(&ival);
    
    Myclass m;
    foo(m);
    
    std::cout << "get_value(ival) = " << get_value(ival) << '\n';
    std::cout << "get_value(&ival) = " << get_value(&ival) << '\n';
    
}
