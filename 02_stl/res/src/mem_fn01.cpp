#include <iostream>
#include <functional>
#include <algorithm>
#include <iterator>
#include <vector>
#include <string>
#include "nutility.h"
#include "date.h"

class Myclass
{
public:
    void func(void)
    {
        std::cout << "Myclass::func() this = " << this << '\n';
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        Myclass m;
        std::cout << "&m = " << &m << '\n';

        auto f = mem_fn(&Myclass::func);
        f(m);

        Myclass* p{ &m };
        f(p);
    }
    {
        Date mdate;

        vector<Date> dvec;
        rfill(dvec, 20, Date::random);
        std::cout << "dvec.size() = " << dvec.size() << '\n';

        vector<int> years;
        years.reserve(dvec.size());

        std::cout << "years.size() = " << years.size() << '\n';

        // transform(dvec.begin(), dvec.end(), back_inserter(years), [] (const Date& d) { return d.year(); });
        transform(dvec.begin(), dvec.end(), back_inserter(years), mem_fn(&Date::year));

        std::cout << "years.size() = " << years.size() << '\n';

        print(years);
    }
}
