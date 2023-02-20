/*
    SORU
        Asagidaki programin ciktisi nedir? 
*/
#include <iostream>

class Nec {
public:
  static int foo() {
      return 777;
  }
  static int x;
};

int foo() { return 5; }
int Nec::x = foo();

int main() {
  std::cout << Nec::x << '\n';
}





















































/*
    Cevap
        777

        Cunku foo ismi icin **name-lookup once class scope**'da yapilir!

        `static int foo()` fonksiyonu olmasaydi cikti 5 olacakti.
        `int Nec::x = ::foo()` olsaydi, cikti 5 olacakti.
*/
