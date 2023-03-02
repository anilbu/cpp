#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <type_traits>  // std::is_same_v

template <typename Iter>
void Advance(Iter& it, int n)
{
    if constexpr (std::is_same_v<typename Iter::iterator_category, std::random_access_iterator_tag>)
    {
        it += n;
    }
    else
    {
        while (n--) ++it;
    }
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
