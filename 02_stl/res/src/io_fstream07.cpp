#include <iostream>
#include <fstream>
#include <iomanip>
#include <filesystem>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    
     gen_text_ifnexists("/tmp/primes.txt", [](ostream& ofs) {
        cout << "Generating file...\n";
        
        // ofs.setf(ios::left, ios::adjustfield);
        // ofs.setf(ios::hex, ios::basefield);
        // ofs.setf(ios::uppercase);
        // ofs.setf(ios::showbase);

        // ofs << left << hex << uppercase << showbase;
        int prime_cnt{};
        int x{ 2 };
        while (prime_cnt < 1'000)
        {
            if (isprime(x)) {
                if (prime_cnt && prime_cnt % 10 == 0)
                    ofs << '\n';
                ofs << setw(10) << x << ' ';
                ++prime_cnt;
            }
            ++x;
        }
    });

    {
        ifstream ifs{ "/tmp/primes.txt" };
        if(!ifs) {
            cerr << "cannot open file!\n";
            return 1;
        }
        
        char c{};
        while(ifs.get(c)){
            cout << static_cast<int>(c) << ' ';
        }
    }
}
