#include <iostream>
#include <string>
#include <vector>
#include <iterator>



int main(int argc, char const *argv[])
{
    using namespace std;
    int a[] = { 2, 6, 7, 1, 7, 0, 98 };
    vector<int> ivec{1, 4, 5, 7, 1};
    
    std::cout << "empty(vector<int>{}) = " << empty(vector<int>{}) << '\n';
    std::cout << "ivec.empty() = " << ivec.empty() << '\n';
    std::cout << "empty(ivec) = " << empty(ivec) << '\n';
    std::cout << "empty(a) = " << empty(a) << '\n';
    
}
