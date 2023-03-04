#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "nutility.h"
#include "date.h"
#include <boost/functional/hash.hpp>

int main(int argc, char const *argv[])
{
    using namespace std;

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
