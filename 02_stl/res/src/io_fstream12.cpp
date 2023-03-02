/**
 *  bir ali.exe 1000
 *
 */

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <numeric>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    auto ifs = open_binary_file("/tmp/primes.dat");
    vector<int> ivec(1'000'000);
    
    ifs.read(reinterpret_cast<char*>(ivec.data()), sizeof(int) * ivec.size());
    std::cout << "ifs.gcount() = " << ifs.gcount() << '\n';
    std::cout << "ivec.size() = " << ivec.size() << '\n';
    
    auto toplam = accumulate(ivec.begin(), ivec.end(), 0LL);
    std::cout << "toplam = " << de(toplam) << '\n';
}
