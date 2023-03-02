#include <iostream>
#include <string>
#include <vector>
#include <iterator>



int main(int argc, char const *argv[])
{
    using namespace std;
    int a[] = { 2, 6, 7, 1, 7, 0, 98 };
    vector<int> ivec{1, 4, 5, 7, 1};
    
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    std::cout << "size(ivec) = " << size(ivec) << '\n';
    std::cout << "size(a) = " << size(a) << '\n';
    
}
