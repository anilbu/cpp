#include <iostream>
#include <functional>
#include <vector>
#include <string>

using namespace std;

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        int x = 10;
        int y = 20;

        reference_wrapper r = x;

        std::cout << "x = " << x << '\n';
        std::cout << "r = " << r << '\n';

        ++r;

        std::cout << "x = " << x << '\n';
        std::cout << "r = " << r << '\n';

        // reference rebind ediliyor
        // int& olsaydi, x'e 20 degeri atanmis olmasi gerekirdi!
        r = y;

        std::cout << "x = " << x << '\n';
        std::cout << "r = " << r << '\n';
    }
    {
        string s1{ "Anil" }, s2{ "Murat" }, s3{ "Necati" };
        using strref = std::reference_wrapper<string>;
        
        vector<strref> svec{s1, s2, s3};

        for (const auto &r : svec)
        {
            cout << r.get() << '\n';
        }
    }
}