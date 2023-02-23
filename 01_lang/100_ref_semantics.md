# Reference Semantics
Reference semantigi sadece dil katmaninda olan bir ozelliktir. Makina kodu seviyesinde bir farklilik saglamamaktadir.

Modern C++'da 3 farkli tip reference vardir:
1. L Value References
2. R Value References
   * Move semantics
   * Perfect forwarding
3. Forwarding Reference (Universal Reference)


## Lvalue references
Bir nesnenin yerine gecen bir identifierdir.

```C++
int x = 10;
int& r = x;
```
`r` ifadesinin turu `int`dir, `r` degiskenin turu `int&`dir. Pointer ifadelerin benzer sekilde:
```C++
int* p = &x;
p   //  p = int*
*p  // *p = int

r   //  r ifadesi = int, r degiskeni = int&
```

* Ref'ler default initialize edilemez. Ilk deger verilmesi zorunludur.
* Ref'ler initialize edildikten sonra tekrar baska bir nesneye baglanamaz.
  *Atama operatoru ref edilen nesnenin degerini degistiriyor.*
* Ref'ler ile referans edilen nesne turlerinin uyumlu olmasi gerekmektedir. (implicit tur donusumu soz konusu degildir)
* Lvalue ref'e, rvalue expr ile ilk deger verilemez.
* Bir rvalue ref, `&` operatorunun operandi olarak verildiginde bagli oldugu nesnenin adresini doner.
  [Ornek](res/src/ref_sem01.cpp)
  ```C++
  int x = 10;
  int& r = x;
  &r == &x;     // true
  ```
* Ref-to-ref kullanimi mumkun degildir.
  ```C++
  int x = 10;
  int& r1 = x;
  int& r2 = r1; // r1 hangi nesneye bagli ise r2 de ona baglanacaktir.
  ```
* Ref-to-pointer
  [Ornek](res/src/ref_sem02.cpp)
  ```C++
  int* p = nullptr;
  int*& p_ref = p;    // ref to int pointer type
  ```
* Ref-to-array
  [Ornek](res/src/ref_sem03.cpp)
  ```C++
  int a[5] { 1, 2, 3, 4, 5};    // int[5]
  int (&ra)[5] = a;             // int[5] turunden bir diziye reference
  ```
  ```C++
  // typedef int ar_type[5];
  using ar_type = int[5];       // ar_type is int[5] type
  ar_type& ar = a;
  ```
* Ref-to-object
  [Ornek](res/src/ref_sem04.cpp)
  ```C++
  struct Data{ int a, b, c };
  Data mydata { 3, 6, 7 };
  Data& rx = mydata;
  ```
* Ref-to-function
  [Ornek](res/src/ref_sem05.cpp)
  ```C++
  int foo(int x);
  int (&rf)(int) = foo;     // fr is a function reference
  ```

<!--  -->

* Referenslar genel olarak su iki amacla kullanilir:
  1. Bir nesneyi bir fonksiyona *call by reference* olarak arguman verilmesi
  2. Bir fonksiyonun kendisini cagiran koda bir nesnenin kendisini iletmesi

  [Ornek](res/src/ref_sem06.cpp)
  
  > **Not**
  > C dilinde pointerlar kullanmadan call by reference kullanimi mumkun degildir. Bu durum C++ icin gecerli degildir.
  
  > **Not**  
  > C dilinde fonksiyon cagri ifadesi karsiligi her zaman rvalue expr'dir. C++ dilinde ise geri donus degir bir ref turunden ise lvalue expr olabilir.
  
  > **DIKKAT!**  
  > Omuru sonlanmis bir nesneyi referans olarak geri dondurmek **UB**dir!
  > [bknz: storage classes](090_storage_classes.md)
  
### Lvalue refs ve `const`

* Bir ref'in baska bir nesneye baglanmasi soz konusu olmadigi icin ref'lerde const'luk low-level constluktur.
  ```C++
  int x = 45;
  const int& r = x; // r is a lvalue ref to const int
  r++;              // sentaks hatasi
  ```
  ```C++
  int& const r = x; // ignore ediliyor: cunku ref zaten dogasi geregi top-level const
  ```

* `const` bir degisken sadece `const &`e baglanabilir
  ```C++
  const int cx = 10;
  const int& cr = cx;
  ```
  ```C++
  int& r = cx;  // sentaks hatasi
  int* p = &cx; // sentaks hatasi
  ```

* Normalde ref initializationda tur donusumu uygulanmamasina ragmen `const&`'lere farkli turden ve deger kategorisinde bulunan nesneler baglanabilir.
  ```C++
  int x = 10;
  double& dr = x;       // not legal: type mismatch
  const double& dr = x; // legal
  ```
  Bu durumda derleyici ref turune uygun olarak bir temp object olusturur ve implicit conversion burada uygulanir. Olusturulan gecici nesne ref'e baglanir. 
  Temp object olusturma islemi sembolik olarak soyle ifade edilebilir:
  ```C++
  double temp_obj = x;          // legal: implicit conv
  const double& dr = temp_obj;  // legal
  ```
  Ayni durum bir `const&`e bir rvalue baglanirken de uygulanir. Olusturulan gecici nesnenin deger kategorisi lvalue .
  ```C++
  int& ir = 45;                 // not legal, 45 is prvalue
  const int& ir = 45;           // legal
  ```
  Sembolik olarak:
  ```C++
  int temp_obj = 45;
  const int& ir = temp_obj;     // legal: temp_obj bir lvalue
  ```
  Bu ozellik fonksiyon parametrelerinde cok sik olarak kullanilmaktadir.
  ```C++
  void func(T&);      // cannot be called with rvalue
  void foo(const T&); // can be called with rvalue
  ```

<!--  -->

  > **setter / mutator functions**
  > Parametre func fonksiyonu tarafindan degeri degistirilebilir.
  > ```C++
  > void func(T&);
  > ```
  > **getter / accessor functions**
  > Parametre func fonksiyonu icinde degeri degistirilemez.
  > ```C++
  > void func(const T&);
  > ```
  
  
## pointers vs references

* Pointer icin ilk deger vermek mecburi degil *verilmemesi yine de onerilmez*, ancak ref'de zorunludur.
* Bir pointer `nullptr` olabilir, ref `nullptr` olamaz.
  *Ornegin, bazi fonksiyonlar basarisiz oldugunda `nullptr` donebilirler. Bazi fonksiyonlar ise opsiyonel olarak bir nesne adresi isteyebilirler.*
* Pointer'lar nesne adresi terkardan atanabilirken, ref'ler yeni bir nesne bind etmek mumkun degildir.
* **pointer-to-pointer** var ancak **ref-to-ref** yoktur.
  *[bknz: reference collapsing](110_type_deduction.md#reference-collapsing)*
* Elemanlari pointer turu olan dizi olusturulabilirken, dogrudan elemanlari ref turu olan bir dizi olusturulamaz.
  ```C++
  int x, y, z;
  int* pa[] = {&x, &y, &z}; // legal: pointer array
  //int& ra[] = {x,y,z};    // not legal
  ```

## Rvalue references
```C++
int&& r = 10;
```
* Rvalue ref'e, rvalue expr ile ilk deger verilmesi zorunludur.

Asagida bildirilen fonksiyonlar hangi deger kategorilerine sahip ifadeler ile cagrilabilir?
```C++
                      // lvalue arg   rval arg
void f1(T &);         // evet         hayir   
void f2(T &&);        // hayir        evet    
void f3(const T &);   // evet         evet    
```




## Reference collapsing

C++ dilinde bir referansa referans olusamaz. Eger bir baglamda ref-to-ref durumu olusuyor ise **reference collapsing** uygulanir. Bu durum iki sekilde olusabilir: **type-deduction** yada **type-alias** kullanilirken.

|     |       | result |
| --- | :---: | :----: |
| T&  |   &   |   T&   |
| T&  |  &&   |   T&   |
| T&& |   &   |   T&   |
| T&& |  &&   |  T&&   |

```C++
using lref = int&;
using rref = int&&;

int i = 10;
lref& x = i;    // &  + &  =>  &
lref&& x = i;   // &  + && =>  &

rref& x = i;    // && + &  =>  &
rref&& x = i;   // && + && =>  &&
```