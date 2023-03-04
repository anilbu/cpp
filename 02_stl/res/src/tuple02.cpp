#include <iostream>
#include <tuple>
#include <string>
#include <vector>
#include <iomanip>
#include <algorithm>

#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        tuple x{ 12, 6.7, "ahmet"s };

        ++get<0>(x);
        get<1>(x) = 3.14;
        get<2>(x) = "nuri";
        // auto val = get<3>(x);   // sentaks error

        get<int>(x) = 10;
    }
    {
        using id = int;
        using name = string;
        using wage = double;

        using person = tuple<id, name, wage>;

        tuple<id, name, wage> tx1;
        person tx2;
        vector<person> pvec;

        // ...

        get<id>(tx1) = 1;
    }

}
