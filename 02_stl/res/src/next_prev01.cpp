#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iterator>

template <typename Iter>
void Print(Iter beg, Iter end)
{
    while (beg != end) {
        std::cout << *beg++ << ' ';
    }
    std::cout << "\n------------------\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;

    vector<int> ivec { 1, 3, 5, 7, 9};
    Print(next(ivec.begin()), prev(ivec.end()));

    list<int> ilst { 1, 3, 5, 7, 9};
    Print(next(ilst.begin()), prev(ilst.end()));

    {
        auto iter = ivec.begin();
        cout << *std::next(iter, 5) << '\n';     // returns iter + 5
        cout << *std::next(iter) << '\n';        // returns iter + 1
    }
    {
        auto iter = ivec.end();
        cout << *std::prev(iter, 5) << '\n';     // returns iter - 5
        cout << *std::prev(iter) << '\n';        // returns iter - 1
    }
}
