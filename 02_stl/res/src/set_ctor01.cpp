#include <iostream>
#include <set>
#include <map>
#include <functional>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        {
            set<int> iset;
        }
        {
            set<int> iset { 1, 6, 3, 2, 6, 9, 5};
            print(iset);
        }
        {
            vector<int> ivec;
            rfill(ivec, 20, Irand{ 0, 200});
            print(ivec);
            
            set<int> iset(ivec.begin(), ivec.end());
            print(iset);
        }
        {
            
        }
    }
}
