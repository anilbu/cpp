#include <iostream>
#include <stack>
#include <string>
#include <list>
#include <vector>
#include <deque>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        stack<int> istack1;                    // stack<int, deque<int>>
        stack<int, list<int>> istack2;
        stack<int, vector<int>> istack3;
    }
    {
        deque<int> ideq { 2, 6, 7, 9, 12};
        stack<int, deque<int>> istack1{ ideq };
        stack<int, deque<int>> istack2{ std::move(ideq) };

        stack istack3{ ideq };    // CTAD
    }

    {
        // Constructorlar explicit'dir.
        // stack<int> istack = ideq;   // sentaks hatasi
    }
    {
        // Range contructor [C++23] ile eklendi.
#if __cplusplus >= 202300L
        vector<int> ivec { 0, 1, 2, 3, 4, 5, 6, 7};
        stack<int> istack(ivec.begin() + 1, ivec.begin() + 4);
#endif
    }
    {
        stack<string> sstack;

        for (int i = 0; i < 10; ++i)
        {
            auto name = rname();
            sstack.push(name);
        }

        std::cout << "sstack.size() = " << sstack.size() << '\n';
        sstack.top() += "can";

        while (!sstack.empty())
        {
            cout << sstack.top() << '\n';
            sstack.pop();
        }
    }
}