#include <iostream>

template <typename T>
void print(const T&){
    std::cout << "[Non-variadic] " << __PRETTY_FUNCTION__ << '\n';   // gcc, clang
}

template<typename T, typename ...Ts>
void print(const T& arg, const Ts& ...args)
{
    std::cout << "[Variadic    ] " << __PRETTY_FUNCTION__ << '\n';
    
    print(arg);
    print(args...);
}

int main(int argc, char const *argv[])
{
    print(10, 23.5, 9L, "necati");
}
