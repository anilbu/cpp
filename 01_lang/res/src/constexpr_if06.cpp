/*
template<int N>
constexpr int fibonacci() { return fibonacci<N - 1>() + fibonacci<N - 2>(); }

template<>
constexpr int fibonacci<1>() { return 1; }

template<>
constexpr int fibonacci<0>() { return 0; }
*/

template<int N>
constexpr int fibo()
{
    if constexpr (N >= 2)
        return fibo<N - 1>() + fibo<N - 2>();
    else
        return N;
}

int main()
{
    constexpr auto y = fibo<8>();
}
