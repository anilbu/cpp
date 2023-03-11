#include <iostream>
#include <type_traits>

template <typename T>
void func_impl(T x, std::true_type)
{
    // T turu bir pointer turu ise bu implementasyon
    std::cout << "Pointer turleri icin bu implementasyon\n";
}

template <typename T>
void func_impl(T x, std::false_type)
{
    // T turu bir pointer turu degil ise bu implementasyon
    std::cout << "Pointer olmayan turler icin bu implementasyon\n";
}

template <typename T>
void func(T x)
{
    func_impl(x, typename std::is_pointer<T>::type{});
}

int main(int argc, char const *argv[])
{
    using namespace std;
    int ival{};
    func(ival);
    func(&ival);
}