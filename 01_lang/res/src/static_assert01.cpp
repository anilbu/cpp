#include <type_traits>
#include "nutility.h"

template<int n>
class Myclass {
    static_assert(ndigit(n) == 3, "N 3 haneli bir sayi olmali");
};

template <typename T>
void func(T x)
{
    static_assert(
        std::is_same_v<T, int> || 
        std::is_same_v<T, long int> || 
        std::is_same_v<T, long long>   
    );
}


template <typename T>
T get_value(T x) {

    if constexpr(std::is_pointer_v<T>){
        return *x;
    }
    else {
        
        return x;
    }
}

int main(int argc, char const *argv[])
{
    static_assert(sizeof(long) > 4, "long turu 4 bytedan buyuk olmali");
    
    
    Myclass<200> x;
    
    int ival{};
    get_value(ival);
}