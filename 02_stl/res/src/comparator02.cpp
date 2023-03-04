#include <iostream>
#include <set>
#include "nutility.h"
#include "date.h"
#include <functional>


int main(int argc, char const *argv[])
{
    using namespace std;

    auto fcyear = [](const Date& a, const Date& b) {
        return a.year() < b.year();
    };

    auto fcmon = [](const Date& a, const Date& b) {
        return a.month() < b.month();
    };

    {
        set<Date, decltype(fcyear)> dset;
        rfill(dset, 20, Date::random);
        print(dset, "\n");
    }
    {
        multiset<Date, decltype(fcyear)> dset;
        rfill(dset, 20, Date::random);
        print(dset, "\n");
    }
    {
        set<Date, decltype(fcmon)> dset;
        rfill(dset, 10, Date::random);
        print(dset, "\n");
    }
    {
        multiset<Date, decltype(fcmon)> dset;
        rfill(dset, 20, Date::random);
        print(dset, "\n");
    }
}
