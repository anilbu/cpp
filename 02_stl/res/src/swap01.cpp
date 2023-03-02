#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        string fname{ "ali" };
        string lname{ "can" };
        cout << fname << ' ' << lname << '\n';

        swap(fname, lname);
        cout << fname << ' ' << lname << '\n';
    }
    {
        vector<int> ivec { 1, 3, 5, 7, 9};
        auto iter1 = ivec.begin();
        auto iter2 = ivec.end() - 1;
        print(ivec);
        std::cout << "*iter1 = " << *iter1 << '\n';
        std::cout << "*iter2 = " << *iter2 << '\n';

        swap(iter1, iter2);
        std::cout << "*iter1 = " << *iter1 << '\n';
        std::cout << "*iter2 = " << *iter2 << '\n';
        print(ivec);
    }
    {
        vector<int> ivec { 1, 3, 5, 7, 9};
        auto iter1 = ivec.begin();
        auto iter2 = ivec.end() - 1;
        print(ivec);
        std::cout << "*iter1 = " << *iter1 << '\n';
        std::cout << "*iter2 = " << *iter2 << '\n';

        swap(*iter1, *iter2);
        std::cout << "*iter1 = " << *iter1 << '\n';
        std::cout << "*iter2 = " << *iter2 << '\n';
        print(ivec);
    }
}
