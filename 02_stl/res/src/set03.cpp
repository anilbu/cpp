#include <iostream>
#include <string>
#include <set>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        set<string> sset { "ali", "ayse", "tarkan", "tekin", "yelda" };
        rfill(sset, 10, []{return rname() + ' ' + rfname(); });
        print(sset);
        
        if(auto iter = sset.find("tekin"); iter != sset.end()) {
            std::cout << "bulundu\n";
            std::cout << "*iter = " << *iter << '\n';
            std::cout << "distance(sset.begin(), iter) = " << distance(sset.begin(), iter) << '\n';
        }
        else {
            std::cout << "bulunamadi\n";
        }
    }
    {
        set<string> sset { "ali", "ayse", "tarkan", "tekin", "yelda" };
        rfill(sset, 10, []{return rname() + ' ' + rfname(); });
        print(sset);
        
        if(auto iter = sset.find("tekin"); iter != sset.end()) {
            std::cout << "bulundu\n";
            std::cout << "*iter = " << *iter << '\n';
            std::cout << "distance(sset.begin(), iter) = " << distance(sset.begin(), iter) << '\n';
        }
        else {
            std::cout << "bulunamadi\n";
        }
    }
}
