#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include "nutility.h"

template <typename FwdIter, typename Fn>
void Generate(FwdIter beg, FwdIter end, Fn f)
{
    while(beg != end) {
        *beg++ = f();
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    unsigned int a[100];
    mt19937 eng{ random_device{}() };
    
    // Generate(begin(a), end(a), ref(eng));
    generate(begin(a), end(a), ref(eng));
    
    print(a);
    
    cout << "--------------------\n";
    
    vector<string> svec(5);
    generate_n(svec.begin(), 5, rname);
    print(svec);
    
    cout << "--------------------\n";
    
    vector<string> svec2;
    generate_n(back_inserter(svec2), 10, []{return rname() + rfname();});
    print(svec2);
    
}
