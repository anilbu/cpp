#include <iostream>
#include <list>
#include <iterator>
#include "nutility.h"
#include "date.h"

using namespace std;


int main(int argc, char const *argv[])
{
    {
        list<string> slist{"belma", "hakki", "necmettin", "gizem"};
        print(slist);

        slist.push_front("cumhur");
        slist.push_back("nalan");
        print(slist);

        auto iter = next(slist.begin(), 3);
        slist.insert(iter, "talat");
        print(slist);

        while (!slist.empty())
        {
            std::cout << "slist.front() = " << slist.front() << '\n';
            slist.pop_front();
            // (void)getchar();
        }
    }
    {
        list<string> slist{"belma", "hakki", "necmettin", "gizem"};
        print(slist);

        slist.front() += "naz";
        slist.back() += "su";
        print(slist);
    }
    {
        list<string> slist;
        rfill(slist, 20, rtown);
        print(slist);
        
        for (auto iter = slist.cbegin(); iter != slist.cend(); ++iter)
        {
            std::cout << *iter << ' ';
        }
        std::cout << "\n-----------------\n";
        
        for (auto iter = slist.crbegin(); iter != slist.crend(); ++iter)
        {
            std::cout << *iter << ' ';
        }
        std::cout << "\n-----------------\n";
        
        for(const auto& e : slist) 
        {
            std::cout << e << ' ';
        }
        std::cout << "\n-----------------\n";
    }
    {
        list<Date> dlist;
        
        dlist.emplace_front(1, 1, 1987);
        dlist.emplace_back(31, 12, 1989);
        dlist.emplace(next(dlist.begin()), 31, 12, 1989);
        
        print(dlist);
    }
}
