#include <iostream>
#include <random>
#include <algorithm>
#include <vector>

// template<typename InIter, typename OutIter, typename Pred>
// OutIter Copy_if(InIter beg, InIter end, OutIter dest_beg, Pred f)
// {
//     while(beg != end)
//     {
//         if(f(*beg))
//             *dest_beg++ = *beg;
//         ++beg;
//     }
    
//     return dest_beg;
// }

int main(int argc, char const *argv[])
{
    using namespace std;

    vector<int> ivec{10000};
    vector<int> dest_vec{10000};
    
    mt19937 eng;
    auto f = [eng](int x) mutable { return eng() % x == 0; };
    copy_if(ivec.begin(), ivec.end(), dest_vec.begin(), f);
}
