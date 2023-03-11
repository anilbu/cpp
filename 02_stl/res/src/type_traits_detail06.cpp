#include <iostream>
#include "nutility.h"


template <typename T>
struct RemoveReference {
    using type = T;
};

template <typename T>
struct RemoveReference<T&> {
    using type = T;         //  T& turleri icin type = T
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;         // T&& turleri icin type = T
};

template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;



template <typename T>
void func(T){
    typename RemoveReference<T>::type x;
    RemoveReference_t<T> y;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    typedef RemoveReference<int>::type   x1;    // x1 = int
    typedef RemoveReference<int&>::type  x2;    // x2 = int
    typedef RemoveReference<int&&>::type x3;    // x3 = int
    RemoveReference_t<double&&> x4;             // x4 = double
}
