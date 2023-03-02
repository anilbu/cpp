#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<int> ivec{ 1, 2, 3, 5, 7, 9};
        vector<int> dest_vec {};
        print(ivec);
        print(dest_vec);
        
        auto logic_end = remove_copy(ivec.begin(), ivec.end(), back_inserter(dest_vec), 2);
        
        print(ivec);
        print(dest_vec.begin(), logic_end);
    }
    {
        vector<string> svec_src = {};
        vector<string> svec_dst;
        size_t len = 5;

        remove_copy_if(svec_src.begin(), svec_src.end(), back_inserter(svec_dst), [len](const string& s) {
            return s.size() >= len;
            });
    }
}
