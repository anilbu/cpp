#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>


int main(int argc, char const *argv[])
{
    using namespace std;
    
    std::cout << boolalpha;
    
    {
        ifstream ifs{};
        std::cout << "ifs.is_open() = " << ifs.is_open() << '\n';
        
        ifs.open("fstream01.txt");
        std::cout << "ifs.is_open() = " << ifs.is_open() << '\n';
        
        ifs.close();
        std::cout << "ifs.is_open() = " << ifs.is_open() << '\n';
        
        ifstream non_exist_ifs {"non_exist.txt"};
        std::cout << "non_exist_ifs.is_open() = " << non_exist_ifs.is_open() << '\n';
    }
    
}
