#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <nutility.h>


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> svec{};
        print(svec);

        string s;
        for (int i = 0; i < 5; i++)
        {
            s = rname();
            svec.push_back(s);
            print(svec);
        }
    }
    {
        vector<string> svec{};
        print(svec);

        string s;
        for (int i = 0; i < 5; i++)
        {
            s = rname();
            svec.push_back(std::move(s));
            print(svec);
        }
    }
}
