#include <iostream>
#include <random>

int main(int argc, char const *argv[])
{
    using namespace std;
    
    mt19937 eng;
    cout << "default seed value: " << eng.default_seed << '\n';
    
    for (size_t i = 0; i < 10'000 - 1; i++)
    {
        (void) eng();
    }
    
    cout << "4123659995 == " << eng() << '\n';
    
    mt19937_64 eng64;
    cout << "default seed value: " << eng64.default_seed << '\n';
    
    for (size_t i = 0; i < 10'000 - 1; i++)
    {
        (void) eng64();
    }
    
    cout << "9981545732273789042 == " << eng64() << '\n';
    
}
