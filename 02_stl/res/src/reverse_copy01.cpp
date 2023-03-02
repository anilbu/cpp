#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    int a[] = { 1, 3, 4, 6, 7, 9, 12 };
    int b[std::size(a)]{};

    print(begin(a), end(a));
    print(begin(b), end(b));

    reverse_copy(begin(a), end(a), begin(b));
    print(begin(a), end(a));
    print(begin(b), end(b));

}
