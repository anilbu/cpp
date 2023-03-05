#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>
#include <string>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    vector<string> svec;
    rfill(svec, 10, rname);
    print(svec);

    copy(svec.begin(), svec.end(), ostream_iterator<string>{ cout, ", " });
    std::cout << "\n";
}
