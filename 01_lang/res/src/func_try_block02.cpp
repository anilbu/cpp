#include <iostream>

class Member {
public:
    Member(){
        throw std::runtime_error{"Member throws an exception!"};
    }
};

class Myclass {
public:
    Myclass()
    try{
        
    }
    catch(const std::exception& ex) {
        std::cout << "hata ctor icinde yakalandi: " << ex.what() << '\n';
        // throw;   // yazilmaz ise derleyici kendisi ekliyor
    }
private:
    Member mx;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    
    try
    {
        Myclass m;
    }
    catch(const std::exception& ex)
    {
        std::cout << "hata main icinde yakalandi: " << ex.what() << '\n';
    }
    
    std::cout << "main devam ediyor\n";
    
}
