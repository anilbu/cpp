#include <iostream>

/*
#define asize(a)    (sizeof(a)/sizeof(*a))
*/

// yerine
// template type deduction kullanilarak bir dizinin boyutunun elde edilmesi:

template <typename T, std::size_t sz>
constexpr std::size_t asize(const T(&)[sz])
{
    return sz;
}

int main(int argc, char const *argv[])
{
    int arr[] {1, 2, 3, 4, 5};
    
    constexpr auto sz = asize(arr);
    std::cout << "asize(arr) = " << asize(arr) << '\n';
    
    return 0;
}
