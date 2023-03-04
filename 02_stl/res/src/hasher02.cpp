#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "nutility.h"
#include "date.h"
#include <boost/functional/hash.hpp>

// std::hash<Date> template specialization
template<>
struct std::hash<Date> {
    size_t operator()(const Date& val) {
        return val.year() + 10'000 * val.month() + 1000'000 * val.month_day();
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        // specialization ornegi
        unordered_set<Date> duset;   // unordered_set<Date, hash<Date>> duset;
    }
    {
        struct DateHasher {
            size_t operator()(const Date& val) const {
                return val.year() + 10'000 * val.month() + 1000'000 * val.month_day();
            }
        };

        unordered_set<Date, DateHasher> duset;
    }
    {
        struct DateHasher {
            size_t operator()(const Date& val) const {
                return val.year() + 10'000 * val.month() + 1000'000 * val.month_day();
            }
        };

        unordered_set<Date, DateHasher> duset;
    }
    {
        auto hasher_func = [](const Date& val) noexcept {
            return val.year() + 10'000 * val.month() + 1000'000 * val.month_day();
        };

        unordered_set<Date, decltype(hasher_func)> duset;
    }
    {
        struct DateHasher {
            size_t operator()(const Date& val) const {
                // hash_val(val.year(), val.month(), val.month_day());
                size_t hashcode = 0U;
                boost::hash_combine(hashcode, val.year());
                boost::hash_combine(hashcode, val.month());
                boost::hash_combine(hashcode, val.month_day());
                return hashcode;
            }
        };

        unordered_set<Date, DateHasher> duset;
    }
}
