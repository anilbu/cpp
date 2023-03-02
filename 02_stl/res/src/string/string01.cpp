#include <iostream>
#include <string>


int main(int argc, char const *argv[])
{
    using namespace std;
    
    std::cout << "sizeof(char*) = " << sizeof(char*) << '\n';
    std::cout << "sizeof(string) = " << sizeof(string) << '\n'; // SBO nedeniyle string sinifi (gcc'de) 32 byte
    
}
