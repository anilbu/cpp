#include <iostream>
#include <map>
#include <vector>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        map<int, string> smap;
        int count = 0;
        rfill(smap, 5, [&] {return make_pair(count++, rname()); });
        print(smap, "\n");
        
        smap[10] = "ali";
        print(smap, "\n");
        
        smap[10] += "can";
        print(smap, "\n");
    }
};