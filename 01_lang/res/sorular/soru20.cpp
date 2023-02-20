/*
    Dongu kullanmadan 0'dan 100'e kadar sayilarin yazdirilmasi
        Bu islem sadece compile-time'da nasil yapilabilir?
*/










































































#include <iostream>

using namespace std;

// 1) recursive cozum:
void Cevap1(int x) {
    if (x == 0) return;
    cout << x;
    return Cevap1(x - 1);
}

// 2) static yerel degisken ve array ile cozum:
struct Cevap2 {
    Cevap2() {
        static int x = 0;
        std::cout << x++;
    }
};

// 3) compile-time recursive ile cozum: 
template <int N>
struct Cevap3: Cevap3<N - 1>
{
    Cevap3() {
        cout << N;
    }
};

template<>
struct Cevap3<0> {

};




int main(int argc, char const *argv[])
{
    Cevap1(100);
    
    Cevap2 b[100];

    Cevap3<100> c;
}
