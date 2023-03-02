#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        ofstream ofs{ "/tmp/primes.dat", ios::binary };
        if (!ofs) {
            cerr << "cannot create file\n";
            return 1;
        }

        int x{ 2 };
        int prime_cnt{};
        while (prime_cnt < 1'000'000)
        {
            if (isprime(x)) {
                ofs.write(reinterpret_cast<char*>(&x), sizeof(int));
                ++prime_cnt;
            }
            ++x;
        }
    }
    {
        auto ifs = open_binary_file("/tmp/primes.dat");
        int x{};
        while(ifs.read(reinterpret_cast<char*>(&x), sizeof(int)))
        {
            cout << x << '\n';
        }
    }
    {
        auto ifs = open_binary_file("/tmp/primes.dat");
        ifs.seekg(0, ios::end);
        auto filesz = ifs.tellg() / sizeof(int);
        ifs.seekg(0);
        
        vector<int> ivec;
        ivec.reserve(filesz);
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        std::cout << "ivec.capacity() = " << ivec.capacity() << '\n';
        
        int x{};
        while(ifs.read(reinterpret_cast<char*>(&x), sizeof(int)))
        {
            ivec.push_back(x);
        }
        
        std::cout << "ivec.size() = " << ivec.size() << '\n';
        std::cout << "ivec.capacity() = " << ivec.capacity() << '\n';
        
        int digit;
        cout << "son basamagi girin: ";
        cin >> digit;
        
        auto n = count_if(ivec.begin(), ivec.end(), [digit](int x) {
            return x % 10 == digit;
        });
        
        std::cout << "n = " << n << '\n';
        
    }
}
