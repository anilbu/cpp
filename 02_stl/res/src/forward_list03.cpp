#include <iostream>
#include <iterator>
#include <string>
#include <forward_list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        forward_list<string> x {"a", "x", "x", "x", "b", "c"};
        print(x);

        x.erase_after(x.begin(), next(x.begin(), 4));
        print(x);
    }
    {
        forward_list<string> x {"x", "x", "x", "a", "b", "c"};
        print(x);

        x.erase_after(x.before_begin(), next(x.before_begin(), 4));
        print(x);
    }
}
