#include <iostream>
#include <list>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<string> slist{"belma", "hakki", "necmettin", "gizem", "tekin", "nuri"};
        print(slist);

        slist.reverse();
        print(slist);

        slist.sort();
        print(slist);

        slist.sort(std::greater{});
        print(slist);
    }
    {
        list<string> slist{"belma", "hakki", "necmettin", "gizem", "tekin", "nuri"};
        print(slist);

        slist.erase(next(slist.begin()));
        print(slist);

        slist.erase(prev(slist.end(), 2));
        print(slist);

        slist.erase(slist.begin(), prev(slist.end()));
        print(slist);
    }
    {
        list<int> ilist;
        rfill(ilist, 30, Irand{ 0, 10 });
        print(ilist);

        int ival = 2;
        ilist.remove(ival);
        print(ilist);

        ilist.remove_if([ival](int a)
        {
            return a % ival == 0;
        });
        print(ilist);
    }
    {
        list<int> ilist;
        rfill(ilist, 20, Irand{ 0, 3 });
        print(ilist);

        ilist.unique();
        print(ilist);
    }
    {
        list<int> ilist;
        rfill(ilist, 20, Irand{ 0, 5 });
        print(ilist);

        ilist.unique([](int a, int b) {
            return a % 2 == b % 2;
        });
        print(ilist);
    }
}
