#include <iostream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include "nutility.h"

#define PRINT_FUNC_SIG_LN() (std::cout << _demangle(__PRETTY_FUNCTION__) << "\n")

void print_array(const int* pb, const int* pe)
{
    PRINT_FUNC_SIG_LN();
    while (pb != pe)
    {
        std::cout << *pb++ << ' ';
    }
    std::cout << "\n---------------------\n";

}

template<typename Iter>
void print_range(Iter beg, Iter end)
{
    PRINT_FUNC_SIG_LN();
    while (beg != end)
    {
        std::cout << *beg++ << ' ';
    }
    std::cout << "\n---------------------\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;

    int a[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

    print_array(a, a + 10);
    print_array(a + 3, a + 7);

    print_range(a, a + 10);

    double d[] = { 1.1, 2.2, 3.3, 4.4 };
    print_range(d, d + 4);

    vector<string> svec { "ali", "naz", "irmak"};
    print_range(svec.begin(), svec.end());      // vector<string>::iterator

    list<string> slist { "ali", "naz", "irmak"};
    print_range(slist.begin(), slist.end());    // list<string>::iterator

    set<string> sset { "ali", "naz", "irmak"};
    print_range(sset.begin(), sset.end());    // list<string>::iterator
}
