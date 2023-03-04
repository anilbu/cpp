#include <iostream>
#include <stack>
#include <deque>
#include "nutility.h"

class necstack: public std::stack<int> {
public:
    // Inherited ctor
    using std::stack<int>::stack;

    void print(const char* delim = ",", std::ostream& os = std::cout) const
    {
        for (auto iter = c.cbegin(); iter < c.cend(); iter++)
        {
            os << *iter << delim;
        }
        os << "\n---------------\n";
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    deque<int> ideq { 1, 2, 3, 4, 5};
    necstack x(ideq);

    x.print();
}
