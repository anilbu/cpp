#include <iostream>
#include <bitset>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    Irand rand{ 0, 1'000'000 };

    cout.setf(ios::hex, ios::basefield);
    cout << rand() << '\n';
    cout << rand() << '\n';
    cout << "------------\n";
    
    cout.setf(ios::uppercase);
    cout << rand() << '\n';
    cout << rand() << '\n';
    cout << "------------\n";

    cout.setf(ios::showbase);
    cout << rand() << '\n';
    cout << rand() << '\n';
    cout << "------------\n";
    
    cout.setf(ios::dec, ios::basefield);
    cout << rand() << '\n';
    cout << rand() << '\n';
    cout << "------------\n";

}
