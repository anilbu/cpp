#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

/*
    Asagidaki programin ciktisi nedir?
 */


template<typename C>
void print(const C& c) 
{
    for (const auto& e : c)
    {
        std::cout << e << ' ';
    }
    std::cout << "\n------------\n";
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    vector<int> ivec { 12, 10, 3, 56, 92, 34, 3, 57, 41};
    
    print(ivec);
    
    auto riter = find(ivec.rbegin(), ivec.rend(), 3);
    ivec.erase(riter.base());
    
    print(ivec);
}
