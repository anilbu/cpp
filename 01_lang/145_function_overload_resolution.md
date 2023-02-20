# Function Overload Resolution

Derleyicinin hangi fonksiyonun cagrildigini belirleme surecine **function overload resolution** denir. Kisaca overload resolution terimi de kullanilir.

Cagri yapilacak fonksiyonun tespiti amaciyla derleyici, en fazla 3 basamakli bir sureci isletir:

1. **Candidate functions** tespit edilir.  
   Derleyici fonksiyon cagrisinin yapildigi noktada gonderilen *argumanlara bakilmaksizin* isimleri ayni olan visible tum fonksiyonlar belirlenir.
   *Imzalardan bagimsiz olarak sadece isimleri ayni olan visible fonksiyonlar*

2. **Viable functions** tespit edilir.  
   Her bir candidate function icin fonksiyon imzasi ile kullanilan argumanlarin uyumu test edilir.
   *"eger bu fonksiyon tek basina olsaydi, kullanilan argumanlar ile cagrilmasi legal olur muydu" sorusunun cevabi*
   
3. **Best Match** kurallarina gore 3 durumdan biri uretilir:
   * No match
     Herhangi bir viable fonksiyon bulunamadi. Sentaks hatasi uretilir.
   * Match  
     Bir viable fonksiyon digerlerine ustun gelerek secilir.
   * Ambuguity  
     Iki yada daha fazla viable fonksiyon arasinda en uygununun secilememesi durumudur. Sentaks hatasi uretilir.
     

## Best Match Kurallari
```
exact match > promotion > conversion > user-defined conv > variadic conv
```
<!-- 
```
standard conversion > user-defined conv > variadic conv
``` 
-->
1. Standard conversion
   1. Exact Match
      * Arguman ile parametre turlerinin birebir ayni olmasi
      * **istisna 1**: `T*`'dan `const T*`'a conversion (const conversion) exact match kabul edilir. 
      * **istisna 2**: Array-decay exact match kabul edilir.
      * **istisna 3**: Function-decay exact match kabul edilir.
   2. Promotion
      * integral promotion
      * floating-point promotion (`float`'dan `double`'a donusum)
   3. Conversion (except promotion cases)
      * **istisna 1**: `bool` ve `void*` arasinda her ikisi de viable olmasi durumunda `void*` tercih edilir. 
2. User-define conversion
   * Birden fazla user-defined var ise *ambiguity*
3. Variadic conversion


## Ozel Durumlar

* `T*` ve `const T*` overloadlar arasinda eger arguman `const` ise `const*` overloadu, degilse `T*` overloadu secilir. Benzer durum `T&` ve `const T&` arasinda da vardir.
  [Ornek](res/src/func_over_res01.cpp)
  ```C++
  void func(int*);          // (1)
  void func(const int*);    // (2)
  ```
  ```C++
  int i = 5;
  func(&i);     // 1 cagrilir
  
  const int ci = 5;
  func(&ci);    // 2 cagrilir, 1 zaten viable degil
  ```

* `T&` ve `T&&` arasinda olusan overloadlar icin eger arguman **lvalue expr** ise `T&` olan, **rvalue expr** ise `T&&` secilir.
  ```C++
  // int& vs int&&
  void func(int&);      // (1)
  void func(int&&);     // (2)
  
  int x{};
  func(x);    // 1 cagrilir, cunku 2 viable degil
  func(10);   // 2 cagrilir, cunku 1 viable degil
  ```
  ```C++
  // const int& vs int&&
  void func(const int&); // (1)
  void func(int&&);      // (2)
  
  int x{};
  func(x);    // 1 cagrilir, 2 viable degil
  func(10);   // 2 cagrilir, rvalue expr ile rvalue ref tercih edilir
  ```
  ```C++
  // int& vs const int& vs int&&
  void func(int&);       // (1)
  void func(const int&); // (2)
  void func(int&&);      // (3)
  
  int i = 10;
  const int ci{ 45 };
      
  func(10);   // 3 cagrilir: const int& ile int&& arasinda int&& kazanir
  func(i);    // 1 cagrilir: int& ile const int& arasinda i const olmadigi icin int& cagrilir
  func(ci);   // 2 cagrilir: sadece const int& viable
  ```

* `bool` ile `void*` arasinda bir overload icin `T*` ile cagri yapildiginda her ikiside viable olmasi durumunda `void*` tercih   edilir.
  ```C++
  // (6)
  void func(bool);
  void func(void *);  // overload
  
  int x{};
  func(&x);           // void* cagrilir
  ```


----------------

## Ornekler
* ```C++
  void f(int);        // (1)
  void f(double);     // (2)
  void f(long);       // (3)

  f(3.4);     // exact match: 2
  f(12);      // exact match: 1
  f(12u);     // ambiguity: 1,2,3 arasinda
  f(true);    // promotion: 1
  f(2.3L);    // ambiguity: 1,2,3 arasinda
  f(2.3f);    // promotion: 2
  f('A');     // promotion: 1
  ```
* ```C++
  void func(int x, int y = 0);
  void func(int x);
  
  func(12);     // ambiguity
  ```
* ```C++
  void func(int);   // (1)
  void func(int&);  // (2)
  
  int ival{};
  func(ival);   // ambiguity
  func(10);     // 1 cagrilir, cunku rvalue expr lvalue ref'e baglanamaz.
  ```
* ```C++
  void func(int);           // (1)
  void func(const int&);    // (2)
  
  func(10);     // ambiguity
  ```
  
* ```C++
  // (4)  nullptr
  void func(double*);   // (1)
  void func(int);       // (2)
  
  // #define NULL ((void*)0)
  func(0);        // 1 cagrilir
  func(NULL);     // ambiguity cunku NULL bir void*
  func(nullptr);  // gecerli: func(double*);
  ```
  [bknz: Pointers - nullptr](080_pointers.md#nullptr)

[Soru](sorular/soru08.cpp)
[Soru](sorular/soru09.cpp) [[bknz: Value categories](065_value_categories.md)]

## Birden fazla parametreli overloadlarin resolution durumlari

Birden fazla parametreli overloadlarda fonksiyonlardan birinin secilebilmesi icin secilecek fonksiyonun asagidaki sartlari saglamasi gerekiyor:

* En az bir parametrede digerlerine ustunluk kurmali.
* Diger parametrelerde de ayni olabilir ancak daha kotu olmamalidir.

**Ornek**
```C++
void f(int, double, long);           // (1)
void f(char, int, double);           // (2)
void f(long, unsigned int, float);   // (3)
```

```C++
f(12, );        // (1) digerlerinden kesin daha iyi
                // diger elemanlara bagli olarak ya (3) secilecek yada ambiguity
```
```C++
f(12, 4L, );    // hala 1.nin secilme ihtimali var mi? 
                //      var, cunku digerlerinden daha kotu degil
```
```C++
f(12, 4);       // simdiden ambiguity, ucuncu parametreye bakmam bile.
                // cunku birinci parametrede (1) iyi, ikinci parametrede (2) iyi
```
```C++
f(12, 4u, );    // ambiguity
                // cunku 1.arg'da (1) iyi, 2.arg'da (3) iyi.
```
```C++
f(12, true, );  // ambiguity
                // 1.arg'da (1), 2.arg'da (2) iyi.
```
```C++
f(12, 4L, 4);   // (1) secilir: 1.arg'da (1) iyi ve diger argumanlarda daha kotu degil.
```
```C++
// 2. parametrede ustunluk saglasin.
f(2.3, true, 12);   // (2) secilir: 2.arg'da daha iyi, digerlerinde daha kotu degil.
```
```C++
// 3. parametrede ustunluk saglasin.
f(34L, 3.5L, 12); // (3) secilir
```


<!-- FIXME `bool` to `int` neden digerlerinden daha iyi?-->
