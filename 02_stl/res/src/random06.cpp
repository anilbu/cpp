#include <iostream>
#include <random>
#include <sstream>

int main(int argc, char const *argv[])
{
    using namespace std;

    // program her calistirildiginda farkli sonuc uretilecek
    random_device rd;
    
    for (int i = 0; i < 5; i++)
    {
        std::cout << "rd() = " << rd() << '\n';
    }
    
    // program her calistirildiginda farkli bir seed degeri verilecek
    mt19937 eng{ random_device{}() };
    
    for (int i = 0; i < 5; i++)
    {
        std::cout << "eng() = " << eng() << '\n';
    }
}
