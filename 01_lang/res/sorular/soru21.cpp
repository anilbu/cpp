#include <iostream>

/*
    Asagidaki programin ciktisi nedir?
*/

int x;

int main(int argc, char const *argv[])
{
    int x = x;
    
    std::cout << "x = " << x << '\n';
}














































































/*
    Undefined behaviour: 
        Isim arama once yapilir, main blogunda bulunan        
        
            int x = x;
        
        ifadesinde her iki x de blok icinde tanimlanmis x'i ifade etmektektedir.
*/