#include <iostream>
#include <iterator>
#include <string>
#include <list>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        list<string> x {"d", "e", "f"};
        list<string> y {"a", "b", "c"};

        // y'nin tamamini x'in basina aktar
        x.splice(x.begin(), y);

        std::cout << "x.size() = " << x.size() << '\n'; // 6
        print(x);
        
        std::cout << "y.size() = " << y.size() << '\n'; // 0
        print(y);
    }
    {
        list<string> x {"a", "d", "e", "f"};
        list<string> y {"g", "b", "c"};

        // y'nin 2.elemanindan itibaren x'in basina aktar
        x.splice(next(x.begin()), y, next(y.begin()));    

        std::cout << "x.size() = " << x.size() << '\n'; // 6
        print(x);
        
        std::cout << "y.size() = " << y.size() << '\n'; // 0
        print(y);
    }
    {
        list<string> x {"a", "d", "e", "f"};
        list<string> y {"b", "c", "g"};
        
        // y'nin ilk 2 elemanini x'in basina aktar
        x.splice(next(x.begin()), y, y.begin(), next(y.begin(), 2));

        std::cout << "x.size() = " << x.size() << '\n'; // 6
        print(x);
        
        std::cout << "y.size() = " << y.size() << '\n'; // 0
        print(y);
    }
}
