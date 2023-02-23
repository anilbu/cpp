#include <iostream>

constexpr bool is_prime(int val)
{
    if (val < 2)
        return false;

    if (val % 2 == 0)
        return val == 2;

    for (int i = 3; i <= val; i += 2)
    {
        if (val % i == 0)
            return false;
    }

    return true;
}


int main() {
    constexpr int x = 19012;
    constexpr int y = 11;

    constexpr auto b1 = is_prime(x - y);   // b1 = false
    
    int x = 19001;
    constexpr bool b2 = is_prime(x);       // sentaks hatasi: arguman constexpr olmadigi icin b2 ilklendirilemez
    const bool b3 = is_prime(x);           // legal
}
