#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

#include "cint.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    Cint i1;
    Cint i2(19);
    
    cout << i1 << " ve " << i2 << '\n';
    
    vector<Cint> cvec;
    for(int i = 0; i< 10; ++i) { 
        cvec.emplace_back(rand() % 100);
    }
        
    sort(cvec.begin(), cvec.end());
    
    for(const auto& c : cvec){ 
        cout << c << '\n';
    }
    
    // += ve *=
    Cint c1{ 321 }, c2{ 56 };
    c1 += c2;
    cout << "c1 = " << c1 << '\n';
    cout << "c2 = " << c2 << '\n';
    
    cout << "c1 + c2 + Cint{12} = " << c1 + c2 + Cint{12} << '\n'; 
    
    
    Cint x{rand() % 10 };
    Cint y{rand() % 10 };
    Cint z{rand() % 10 };
    
    cout << x << y << z << '\n';
    cout << x * y + z << '\n';
    
    cout << c1 << -c1 << +c1 << '\n';
    
    return 0;
}
