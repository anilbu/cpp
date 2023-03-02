#include <iostream>
#include "nutility.h"
#include <bitset>


int main(int argc, char const *argv[])
{
    using namespace std;

    std::cout << "4. = " << 4. << '\n';
    cout.setf(ios::showpoint);
    std::cout << "4. = " << 4. << '\n';
    cout << "----------------------\n";
    
    cout << 3.14 << '\n';
    cout << 3.14159 << '\n';
    cout << 3.14159265359 << '\n';
    cout << "----------------------\n";

    cout.setf(ios::fixed, ios::floatfield);
    cout << 3.14 << '\n';
    cout << 3.14159 << '\n';
    cout << 3.14159265359 << '\n';
    cout << "----------------------\n";


    cout.setf(ios::scientific, ios::floatfield);
    cout << 3.14 << '\n';
    cout << 3.14159 << '\n';
    cout << 3.14159265359 << '\n';
    cout << "----------------------\n";


    cout.setf(ios::fixed | ios::scientific, ios::floatfield); // hexfloat
    cout << 3.14 << '\n';
    cout << 3.14159 << '\n';
    cout << 3.14159265359 << '\n';
    cout << "----------------------\n";
    
    cout.setf(ios::fixed, ios::floatfield);
    cout.precision(12);
    std::cout << "precision = " << cout.precision() << '\n';
    
    cout << 3.14 << '\n';
    cout << 3.14159 << '\n';
    cout << 3.14159265359 << '\n';
    cout << "----------------------\n";
    
}
