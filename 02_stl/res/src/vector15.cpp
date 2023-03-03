#include <iostream>
#include <vector>
#include <deque>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    vector<bool> bvec(10);
    deque<bool> bdeq(10);

    // vector<bool>'da auto = bool olmasini beklenirken aslinda turu vector<bool>::reference
    auto b0 = bdeq[0];  // b0 = bool
    auto b1 = bvec[0];  // b1 = std::vector<bool>::reference
    bool b2 = bvec[0];  // b2 = bool (implicit conversion)
    vector<bool>::reference b3 = bvec[0]; // b3 = std::vector<bool>::reference

    cout << _demangle(typeid(b0).name()) << '\n';  // bool
    cout << _demangle(typeid(b1).name()) << '\n';  // std::_Bit_reference
    cout << _demangle(typeid(b2).name()) << '\n';  // bool
    cout << _demangle(typeid(b3).name()) << '\n';  // std::_Bit_reference
}