/*
    Asagidaki kodda ADL var midir? 
*/

#include <iostream>
#include <vector>
#include <algorithm>

int main() {
    // std::cout << "hello world\n";   // (1)
    // std::cout << endl;              // (2)
    // endl(std::cout);                // (3)
    
    std::vector<int> ivec(100);
    // sort(begin(ivec), end(ivec))    // (4)
}



































































/*
    Cevap
    
    (1)
        ADL uygulanir!
        Cunku, operator<<(std::ostream&, const char*) fonksiyonu
        std namespace'i icinde yer alan bir global fonksiyondur
        ve arguman olarak std::cout nesnesi alir!
        
        operator<<(std::cout, "Hello world");
    
    (2)
        syntax hatasi olusur, ADL soz konusu degil.
        std::cout.operator<<(endl);
    
    (3)
        gecerli
        endl global bir fonksiyondur, std::cout argumani verilmesinden dolayi
        ADL uygulanir
        
    (4)
        3 kere ADL uygulanir
        ivec std namespace'i icindeki bir fonksiyona iliskindir.
        begin ve end bu nedenle std icinde bulunur.
        sort fonksiyonu icin de begin yada end geri donus turleri 
        std icinde bulunmasindan dolayi ADL uygulanir.

*/