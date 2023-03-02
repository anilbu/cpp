#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include "nutility.h"

void func(const std::uniform_int_distribution<int>& dist)
{
    std::uniform_int_distribution<int> x;
    
    x.param(dist.param());
}

void func2(std::uniform_int_distribution<int>& dist)
{
    auto tmp = dist.param();
    
    dist.param(tmp);
}

int main(int argc, char const *argv[])
{
    using namespace std;


    

}
