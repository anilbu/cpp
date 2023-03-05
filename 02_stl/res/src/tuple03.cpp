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
    
    using person = tuple<int, string, double>;
    
    vector<person> pvec;
    pvec.reserve(10);

    Irand irand{ 0, 10 };
    Drand drand{ 10.0, 40.0 };

    for (int i = 0; i < 10; ++i)
    {
        pvec.emplace_back(irand(), rname(), drand());
    }

    std::cout << "pvec.size() = " << pvec.size() << '\n';
    sort(pvec.begin(), pvec.end());     // std::less

    std::cout << fixed << setprecision(2);
    for (const auto& t : pvec)
    {
        std::cout << get<0>(t) << " " << get<1>(t) << " " << get<2>(t) << '\n';
    }

}
