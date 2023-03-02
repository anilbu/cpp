#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>

template <typename Iter>
void advance_impl(Iter& it, int n, std::random_access_iterator_tag)
{
    it += n;
}

template <typename Iter>
void advance_impl(Iter& it, int n, std::bidirectional_iterator_tag)
{
    while(n--) ++it;
}

template <typename Iter>
void Advance(Iter& it, int n)
{
    advance_impl(it, n, typename Iter::iterator_category{});
}

int main(int argc, char const *argv[])
{
    using namespace std;

    vector<int> ivec(100);
    list<int> ilist(100);

    auto ivec_iter = ivec.begin();
    Advance(ivec_iter, 60);     // ivec_iter += 60;

    auto ilst_iter = ivec.begin();
    Advance(ilst_iter, 20);    // for(int n = 20; n--; ++ilst_iter);
}
