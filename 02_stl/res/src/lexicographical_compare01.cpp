#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        vector<int> x{1, 3, 5, 7};
        vector<int> y{1, 30, 5, 7};
        
        std::cout << "x < y = " << (x < y) << '\n';
        std::cout << "x > y = " << (x > y) << '\n';
    }
    {
        vector<int> x{1, 3, 5, 7};
        list<int> y{1, 30, 5, 7};
        
        auto res = lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
        std::cout << "res = " << res << '\n';
        
    }
}
