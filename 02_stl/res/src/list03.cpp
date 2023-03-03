#include <iostream>
#include <algorithm>
#include <string>
#include <list>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<string> x, y;

        rfill(x, 10, rname);
        x.sort();
        std::cout << "x.size() = " << x.size() << '\n'; // 10
        print(x);

        rfill(y, 10, rname);
        y.sort();
        std::cout << "y.size() = " << y.size() << '\n'; // 10
        print(y);


        x.merge(y); // y'deki ogeler x'e merge edildi.


        std::cout << "x.size() = " << x.size() << '\n'; // 20
        print(x);
        std::cout << "y.size() = " << y.size() << '\n'; // 0
        print(y);
    }
    {
        list<string> x, y;

        rfill(x, 10, rname);
        x.sort(std::greater{});
        std::cout << "x.size() = " << x.size() << '\n'; // 10
        print(x);

        rfill(y, 10, rname);
        y.sort(std::greater{});
        std::cout << "y.size() = " << y.size() << '\n'; // 10
        print(y);


        x.merge(y, std::greater{}); // y'deki ogeler x'e merge edildi.


        std::cout << "x.size() = " << x.size() << '\n'; // 20
        print(x);
        std::cout << "y.size() = " << y.size() << '\n'; // 0
        print(y);
    }
}
