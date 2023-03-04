#include <iostream>
#include <queue>
#include <string>
#include <list>
#include <deque>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        queue<int> iqueue1;                    // queue<int, deque<int>>
        queue<int, list<int>> iqueue2;
    }
    {
        deque<int> ideq { 2, 6, 7, 9, 12};
        queue<int, deque<int>> iqueue1{ ideq };
        queue<int, deque<int>> iqueue2{ std::move(ideq) };

        queue iqueue3{ ideq };    // CTAD
    }

    {
        // Constructorlar explicit'dir.
        // queue<int> iqueue = ideq;   // sentaks hatasi
    }
    {
        // Range contructor [C++23] ile eklendi.
#if __cplusplus >= 202300L
        list<int> ilist { 0, 1, 2, 3, 4, 5, 6, 7};
        queue<int> iqueue(ilist.begin() + 1, ilist.begin() + 4);
#endif
    }
    {
        queue<string> squeue;

        for (int i = 0; i < 10; ++i)
        {
            auto name = rname();
            squeue.push(name);
        }

        std::cout << "squeue.size() = " << squeue.size() << '\n';
        
        squeue.front() += "can";
        squeue.back() += "su";
        
        std::cout << "squeue.front() = " << squeue.front() << '\n';
        std::cout << "squeue.back() = " << squeue.back() << '\n';

        while (!squeue.empty())
        {
            cout << squeue.front() << '\n';
            squeue.pop();
        }
    }
}