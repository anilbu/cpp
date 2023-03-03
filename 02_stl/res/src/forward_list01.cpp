#include <iostream>
#include <iterator>
#include <string>
#include <forward_list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        forward_list<string> ilist {"b", "c", "d"};

        std::cout << "distance(ilist.begin(), ilist.end()) = " << distance(ilist.begin(), ilist.end()) << '\n';
        print(ilist);
        
        // listenin basina ekle
        x.push_front("a");
        print(x);
        
    }
}
