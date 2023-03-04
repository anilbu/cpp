#include <iostream>
#include <unordered_set>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        unordered_set<string> suset;
        rfill(suset, 100, rname);

        std::cout << "suset.size() = " << suset.size() << '\n';
        std::cout << "suset.bucket_count() = " << suset.bucket_count() << '\n';
        std::cout << "suset.load_factor() = " << suset.load_factor() << '\n';
        std::cout << "suset.max_load_factor() = " << suset.max_load_factor() << '\n';
        
        // suset.max_load_factor(0.7f)
        
        for (size_t i = 0; i < suset.bucket_count(); ++i)
        {
            cout << setw(5) << i << " " << setw(3) << suset.bucket_size(i);
            for(auto iter = suset.begin(i); iter != suset.end(i); ++iter)
            {
                cout << " -> " << *iter;
            }
            cout << '\n';
        }
    }
}


