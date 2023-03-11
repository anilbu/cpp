#include <iostream>
#include <type_traits>
#include "nutility.h"

template <typename T>
void func(T)
{
    static_assert(std::is_same_v<int, T>, "yanlizca int turu");
}

int main(int argc, char const *argv[])
{
    using namespace std;
    func(10);
    func(3.14);  // should fail
}
