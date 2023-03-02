#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    int x;
    
    std::cout << "Bir tam sayi girin (hex):";
    std::cin >> hex >> x;       // type 0x64
    
    // cin.setf(ios::hex, ios::basefield);
    // std::cin >> x;
    
    std::cout << x;             // prints 100
}
