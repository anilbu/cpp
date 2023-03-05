#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <string>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        cout << boolalpha;
        auto f = not_fn(isprime);

        std::cout << "isprime(17) = " << isprime(17) << '\n';
        cout << "f(17) = " << f(17) << '\n';

        std::cout << "isprime(20) = " << isprime(20) << '\n';
        cout << "f(20) = " << f(20) << '\n';
    }
    {
        vector<string> svec;
        rfill(svec, 20, rname);
        print(svec);

        auto fpred = [](const string& s) { return s.length() > 4; };
        cout << count_if(svec.begin(), svec.end(), fpred) << '\n';
        cout << count_if(svec.begin(), svec.end(), not_fn(fpred)) << '\n';
    }
}
