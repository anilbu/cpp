#include <iostream> 

template <typename T>
struct TypeIdentity {
    using type = T;
};

template <typename T>
using TypeIdentity_t = typename TypeIdentity<T>::type;


// template <typename T>
// void func(T x, T y);

template <typename T>
void func(T x, typename TypeIdentity<T>::type y);


int main(int argc, char const *argv[])
{
    func(2.3, 5);
    func(4, 'A');
}
