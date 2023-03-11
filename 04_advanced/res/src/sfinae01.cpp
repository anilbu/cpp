#include <iostream>


template<typename T, unsigned N>
std::size_t len(T(&)[N])                // (1)
{
    return N;
}

template<typename T>
typename T::size_type len(T const& t)   // (2)
{
    return t.size();
}

int main()
{
    {
        int a[10]{};
        std::cout << len(a);
        /*
        std::size_t len<int, 10>(int(&)[10]);       // (1): gecerli
        int*::size_type len<int*>(int* const & t);  // (2): substitution error, overload set'e dahil edilmeyecek (sfinaed-out)
        */
    }
    {
        std::cout << len("tmp");
        /*
        std::size_t len<const char, 4U>(const char (&)[4]);         // (1): gecerli
        const char*::size_type len<const char*>(const char* & t);   // (2): sfinaed-out
        */
    }
    {
        int* p{};
        //std::cout << len(p); //gecersiz
    }
    {
        std::allocator<int> x;
        // std::cout << len(x); //gecersiz
    }
}
