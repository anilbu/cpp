#include <iostream>
#include <type_traits>
#include <iterator>
#include <vector>
#include <list>
#include "nutility.h"



template <typename Iter>
int Distance_impl(Iter beg, Iter end, std::input_iterator_tag)
{
    std::cout << "Distance_impl: input_iterator_tag\n";
    int cnt{};
    while (beg != end)
    {
        ++beg;
        ++cnt;
    }

    return cnt;
}

template <typename Iter>
int Distance_impl(Iter beg, Iter end, std::random_access_iterator_tag)
{
    std::cout << "Distance_impl: random_access_iterator_tag\n";
    return end - beg;
}

template <typename Iter>
int Distance(Iter beg, Iter end)
{
    // return distance_impl(beg, end, typename Iter::iterator_category{});
    return Distance_impl(beg, end, typename std::iterator_traits<Iter>::iterator_category{});
}


int main(int argc, char const *argv[])
{
    using namespace std;

    int arr[] = { 3, 5, 10, 2 };
    list<int> ilist{3, 5, 10, 2};
    vector<int> ivec{3, 5, 10, 2};

    std::cout << "Distance(arr, arr + 4) = ";
    Distance(arr, arr + 4);
    
    std::cout << "Distance(begin(arr), end(arr)) = ";
    Distance(begin(arr), end(arr));
    
    std::cout << "Distance(ivec.begin(), ivec.end()) = ";
    Distance(ivec.begin(), ivec.end());
    
    std::cout << "Distance(ilist.begin(), ilist.end()) = ";
    Distance(ilist.begin(), ilist.end());
}
