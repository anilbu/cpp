#include <iostream>
#include <iterator>
#include <string>
#include <vector>



int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<int> ivec_src {1, 3, 5, 7, 9};
        vector<int> ivec_dst;
        std::cout << "ivec_dst.size() = " << ivec_dst.size() << '\n';

        copy(ivec_src.begin(), ivec_src.end(), back_inserter(ivec_dst));
        std::cout << "ivec_dst.size() = " << ivec_dst.size() << '\n';
    }
}
