#include <iostream>
#include <fstream>
#include <iomanip>
#include <algorithm>
#include <iterator>
#include "nutility.h"



int main(int argc, char const *argv[])
{
    using namespace std;

    gen_bin_ifnexists("/tmp/primes.dat", [](ostream& ofs) {
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
        });

    {
        auto ifs = open_binary_file("/tmp/primes.dat");

        int x{};
        size_t n{};
        while (true) {
            cout << "kacinci asal sayi: ";
            if (!(cin >> n))
                break;
            ifs.seekg(static_cast<streampos>((n - 1) * sizeof(int)));
            ifs.read(reinterpret_cast<char*>(&x), sizeof(int));
            cout << n << ". asal sayi = " << x << '\n';
        }
    }
}
