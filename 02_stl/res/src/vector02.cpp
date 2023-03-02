#include <iostream>
#include <algorithm>
#include <string>
#include <vector>



int main(int argc, char const *argv[])
{
    using namespace std;
    vector<int> ivec(1'000'000);
    
    std::cout << "size =  = " << ivec.size() << " capacity = " << ivec.capacity() << '\n';
    ivec.erase(ivec.begin() + 100, ivec.end());
    std::cout << "size =  = " << ivec.size() << " capacity = " << ivec.capacity() << '\n';
    ivec.clear();
    std::cout << "size =  = " << ivec.size() << " capacity = " << ivec.capacity() << '\n';
    ivec.shrink_to_fit();
    std::cout << "size =  = " << ivec.size() << " capacity = " << ivec.capacity() << '\n';
}
