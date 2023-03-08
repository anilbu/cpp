#include <iostream>
#include <memory>
#include "nutility.h"

class Myclass;

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        Myclass* p;
        // delete p;    // sentaks hatasi: incomplete type'in delete edilmesi
    }
    {
        
        std::unique_ptr<Myclass> ptr;   // sentaks hatasi: Myclass delete edilemez.
    }
    
}
