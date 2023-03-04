#include <iostream>
#include <set>
#include <map>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    
    {
        set<int> iset;
        Irand rand{0, 50};
        
        for (size_t i = 0; i < 50; i++)
        {
            iset.insert(rand());
        }
        
        std::cout << "iset.size() = " << iset.size() << '\n';
        print(iset);
    }
    {
        set<int, greater<int>> iset;
        Irand rand{0, 50};
        
        for (size_t i = 0; i < 50; i++)
        {
            iset.insert(rand());
        }
        
        std::cout << "iset.size() = " << iset.size() << '\n';
        print(iset);
    }
}
