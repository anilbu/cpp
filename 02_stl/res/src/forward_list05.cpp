#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <forward_list>
#include "nutility.h"

template<typename FwIter, typename T>
FwIter find_before(FwIter before_beg, FwIter end, const T& val)
{
    FwIter cur = next(before_beg);
    while(cur != end)
    {
        if(*cur == val){
            return before_beg;
        }
        before_beg = cur++;
    }
    
    return end;
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        forward_list<string> x {"x", "a", "b", "y", "c", "d", "e", "z"};
        print(x);

        if(auto iter = find_before(x.before_begin(), x.end(), "x"); next(iter) != x.end())
        {
            std::cout << "*next(iter) = " << *next(iter) << '\n';
            x.erase_after(iter);
            print(x);
        }
        
        if(auto iter = find_before(x.before_begin(), x.end(), "y"); next(iter) != x.end())
        {
            std::cout << "*next(iter) = " << *next(iter) << '\n';
            x.erase_after(iter);
            print(x);
        }
        
        if(auto iter = find_before(x.begin(), x.end(), "z"); next(iter) != x.end())
        {
            std::cout << "*next(iter) = " << *next(iter) << '\n';
            x.erase_after(iter);
            print(x);
        }
    }
}
