# Operator Overloading
*Operator yuklemesi*  

**Motivasyon**  
Programcinin isini kolaylastirmak. User-defined types icin islemler daha kolay kullanilacak, okunacak. Ornek olarak, matris toplama, string concat vb.
  
2 tip tanimlama yolu vardir: 
  1. Global operator function
  2. Non-static member operator function
     *Operator fonksiyonlari sinifin **static member fonksiyonu olamaz***

Runtime ek maliyeti yoktur.
```C++
a + b;  // aslinda operator+(a, b)
```

## Genel Kurallar
* Operandlardan en az birinin bir `class`/`enum` turunden olmasi gerekir.

* Overload edilen operatorun C++'in operator setinden biri olmasi gerekir.  
  *Olmayan bir operator overload edilemez, yeni bir operator uretilemez.*

* Bazi operatorler overload edilmesi **yasaklanmistir**:
  * `.` operatoru
  * `sizeof` operatoru
  * `?:` operatoru
  * `::` operatoru
  * `.*` operatoru
  * `typeid` operatoru

* Bazi operatorler icin **yanlizca member operator function** olusturulabilir.
  * `[]` operatoru
  * `->` operatoru
  * type cast operatoru
  * `()` operatoru
  * `=` (SFM atama) operatoru

* Operator fonksiyonlari belirli kurallara uygun olarak isimlendirilmelidir.
  ```C++
  operator+
  operator==
  operator++
  operator()    // fonksiyon cagri operatoru
  operator()&   // adres operatoru
  ```

* Tum operator fonksiyonlari isimleri ile de cagrilabilir.  
  *Bazi durumlarda isimleri ile cagirmak gerekebiliyor.*
  ```C++
  int x = 5;
  std::cout << x;
  std::cout.operator<<(x);
  ```
  
* Operator fonksiyonlari bir istisna disinda **default arg alamaz**.  
  *Istisna: `operator()`*
  
* Operatorlerin arity'sine uymak zorundadir.  
  *Unary ise unary, binary ise binary operator olarak overload edilmelidir.*
  
* 4 tane token var ki hem unary hemde binary operator olarak birden fazla anlamda kullanilmaktadir.
  * `+` : sign (+a) ve addition (a + b)
  * `-` : sign (-a) ve subtraction (a - b)
  * `&` : addresof (&a) ve bitwise (a & b)
  * `*` : deferencing (*p) ve multiplication (a * b)

* operator fonksiyonlari kendi icinde overload edilebilir.  
  *operator fonksiyonlari da bir fonksiyon olmasindan dolayi*

* Operatorlerin onceligi (precedence) ya da operatorlerin oncelik yonu (associativity) degistirilemez.

* Ayni seviyede onceligi olan operatorler, oncelik yonune gore calistirilir.

* Hem `=` hemde `+` operatorlerinin overload edilmis olmasi `+=` overload edildigi anlamina gelmez.

* Ayni turler icin hem global hemde member operator fonksiyonu overload etmeyin.  
  *Senaryolarin buyuk kisminda ambiguity olusacaktir!*

## Mantiksal Kurallar
*(Dilin kurallari acisindan zorunlu degil)*

* Operator fonksiyonlari geri donus degerleri **value kategorilerine uymalidir**.
  * Atama operatorleri (=, +=, -= vs.): `T&`
  * Aritmetik operatorler: `T`  
  * `+x` ve `-x` isaret operatorleri: `T`
  * `++x` (lvalue expr): `T&`
  * `x++` (prvalue expr): `T`
  * `[]` operatoru: `T&`
  
* Operator return degeri turu, problem domaine gore mantikli turler olmali.
  ```C++
  class Date {
  public:
    Date operator+(int days) const;
    int operator-(const Date&) const;
    bool operator==(const Date&) const;
    Date& operator=(const char*);
  };
  ```
  
* const correctness  
  *Operatorun yan etkisi var mi?*
  ```C++
  class BigInt {
  public:
    Bigint operator+(const BigInt&) const;
    BigInt& operator=(const BigInt&);
    BigInt& operator+=(const BigInt&);
    bool operator<(const BigInt&) const;
  };
  ```
  
## Global Operator overloading vs Member operator overloading

**Global Operator overloading**  

* Sol operand degeri bir sinif turunden olmadiginda islemin yapilabilmesi icin global operator overloading fonksiyonu kullanilabilir.
  ```C++
  Myclass x;
  x + 5
  5 + x
  ```
  
* Bize ait olmayan bir sinifin operatorunu overload etmek icin 
  ```C++
  Date date;
  std::cout << date;  // std::cout.operator<<(date);
  ```
  `std::cout.operator<<(const Date&)` fonksiyonu `std::cout` sinifina member olarak eklenemeyecegi icin global fonksiyon olarak overload edilebilir:
  ```C++
  std::ostream& operator<<(std::ostream&, const Date&);
  ```

* Global operator fonksiyonunun sinifin private memberlarina erisilmek isteniyorsa `friend` verilebilir.

* `enum` turleri icin bir sinif olmamasi nedeniyle sadece global operator overloading fonksiyonu kullanilabilir.

**Member operator overloading**  

* Sinifin private uyelerine erisimi vardir.

**Global mi Member mi?**

Kesin bir kurali yok ancak bazi ilkeler tavsiye olarak uyulabilir.

* Simetrik binary operatorleri global fonskiyon ile overload edilmesi  
  *`a>b` ve `b>a` ayni anlami ifade ediyor ise*

* Simetrik olmayan binary operatorleri ve unary operatorleri member fonksiyon ile overload edilmesi


