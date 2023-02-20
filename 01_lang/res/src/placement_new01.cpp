#include <iostream>
#include <string>

using namespace std;

class Myclass
{
public:
    Myclass()
    {
        cout << "Myclass() this = " << this << '\n';
    }

    ~Myclass()
    {
        cout << "~Myclass() this = " << this << '\n';
    }

private:
    int x{}, y{}, z{};
    char mstr[40]{};
};

int main(int argc, char const *argv[])
{
    // Myclass turunden bir nesneyi tutabilecek buyuklukte bellek alani
    // buffer dinamik degil, otomatik omurlu bir degisken
    char buffer[sizeof(Myclass)];
    std::cout << "static_cast<void*>(buffer) = " << static_cast<void *>(buffer) << '\n';

    // buffer bellek alaninda bir Myclass nesnesi olusturuluyor
    Myclass* p = new (buffer) Myclass;
    std::cout << "p = " << p << std::endl;
    
        // delete p; // UB
                 // Cunku delete operatoru karsiligi derleyici sinifin dtor'unu cagirip
                 // adres bilgisini operator delete fonksiyonuna gonderiliyor.
                 //
                 // Ancak bellek alani new operatoru ile -heap'de- olusturulmadi.
                 // free yada delete operaturne stack'de olusturulmus 
                 // bir bellek adresi gonderimi UB
    
    // delete p yapilmadigi icin dtor ayrica cagrilmasi gerekir.
    p->~Myclass();  
    
    return 0;
}
