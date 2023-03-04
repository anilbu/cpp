#include <iostream>
#include <tuple>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    tuple<int, double, string> tx;
    using tx_type = decltype(tx);
    
    constexpr auto nElements = tuple_size<tx_type>::value;
    constexpr auto nElements2 = tuple_size_v<tx_type>;
    
    tuple_element<1, tx_type>::type dval{};
    tuple_element_t<1, tx_type> dval2{};
}
