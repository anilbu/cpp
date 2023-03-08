#include <iostream>
#include <type_traits>
#include "nutility.h"

template <typename T>
void func(T x)
{
    // T turu bir pointer turu degil ise sentaks hatasi versin
    static_assert(std::is_pointer<T>::value, "T must be a pointer type");
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int ival{};
    // func(ival);  // sentaks hatasi verilecek: T must be a pointer type
    func(&ival);    // gecerli
}
