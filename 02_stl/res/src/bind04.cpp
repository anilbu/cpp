#include <iostream>
#include <functional>
#include <vector>
#include "nutility.h"
#include <algorithm>
#include <fstream>
#include <iterator>

struct Functor
{
    int operator()(int a, int b, int c) const
    {
        return a * b * c;
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::placeholders;

    // bind'a bir Functor object de verilebilir.
    {
        auto f = bind(Functor{}, _1, _1, _1);
        cout << f(20) << '\n';
    }

    // yada bir lambda expression
    {
        auto f = bind([](int x, int y) { return x + y; }, _1, 100);
        cout << f(20) << '\n';
    }
}