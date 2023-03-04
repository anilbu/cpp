#include <iostream>
#include <tuple>
#include <string>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        tuple<int, double> tx1;
        tuple<int, double, string> tx2{1, 2.3, "str"};
        auto tx3 = make_tuple(12, 3.14, 9.f);
        tuple tx4{ 12, "alican"s, 4.5 };   // (CTAD) tx4 = tuple<int, string, double>
    }

}
