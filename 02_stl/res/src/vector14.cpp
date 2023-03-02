#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"
#include "date.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<Date> dvec;
        dvec.reserve(20);

        dvec.emplace_back();
        dvec.emplace_back(12, 5, 1987);
        dvec.emplace_back("18-02-2022");

        for (const auto& date : dvec)
        {
            std::cout << date << "\n";
        }
    }
    std::cout << "--------------\n";
    {
        vector<Date> dvec;
        
        dvec.push_back(Date{});     // Default ctor + Move ctor
        dvec.emplace_back();        // Default ctor
    }
    std::cout << "--------------\n";
    {
        vector<Date> dvec;
        
        Date m_date;
        dvec.push_back(m_date);     // Copy ctor
        dvec.emplace_back(m_date);  // Copy ctor
    }
}
