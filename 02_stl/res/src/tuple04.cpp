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
        int ival{};
        double dval{};

        pair<int&, double&> p {ival, dval};
        p.first = 10;
        p.second = 3.14;

        cout << p << '\n';
        std::cout << "ival = " << ival << '\n';
        std::cout << "dval = " << dval << '\n';
    }
    {
        int ival{};
        double dval{};
        string sval{};

        tuple<int&, double&, string&> tx {ival, dval, sval};
        get<0>(tx) = 10;
        get<1>(tx) = 3.14;
        get<2>(tx) = "ali";

        cout << tx << '\n';
        std::cout << "ival = " << ival << '\n';
        std::cout << "dval = " << dval << '\n';
        std::cout << "sval = " << sval << '\n';

    }
    {
        tuple x{ 12, "ahmet"s, 6.7 };

        int id;
        string name;
        double wage;

        std::cout << "x = " << x << '\n';
        
        // tuple<int&, double&, string&>{id, name, wage} = x;
        tie(id, name, wage) = x;
    }
    {
        tuple x{ 12, "ahmet"s, 6.7 };
        auto [id, name, wage] = x;

        std::cout << "id = " << id << '\n';
        std::cout << "name = " << name << '\n';
        std::cout << "wage = " << wage << '\n';
    }
}
