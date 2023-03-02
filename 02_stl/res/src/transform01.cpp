#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "nutility.h"



int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<string> slist_src {"ali", "ayse", "mehmet"};
        vector<size_t> ivec_dst(slist_src.size());

        std::transform(slist_src.begin(), slist_src.end(), ivec_dst.begin(), [](const string& x) {
            return x.size();
        });
        
        print(ivec_dst);
    }
    {
        vector<int> ivec {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

        std::transform(ivec.begin(), ivec.end(), ivec.begin(), [](int x) {
            return x * x;
            });
            
        print(ivec);
    }
    {
        list<string> slist_src {"ali", "ayse", "mehmet"};
        vector<string> svec_src {"kaya", "demir", "oz" };
        vector<string> svec_dst {};

        std::transform(slist_src.begin(), slist_src.end(), svec_src.begin(),
            back_inserter(svec_dst),
            [](const string& a, const string& b) {
                return a + ' ' + b;
            }
        );
        
        print(svec_dst, "\n");
    }

}
