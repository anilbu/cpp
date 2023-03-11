# Function Overloading

Ozunde -soyut olarak- ayni isi yapan fonksiyonlarin, kodlarinin farkli olmasina ragmen, ayni isimde olusturulabilmesini saglayan bir mekanizmadir.

Function overloading [**static binding**](999_kavramlar.md#static-binding) (compile-time) bir mekanizmadir.

**Ornek**
`operator+` farkli turler icin farkli instructionlar uretilse de ayni isi yapiyor:
```C++
i1 + i2
d1 + d2
s1 + s2
```

Overloading mekanizmasinin isler hale gelebilmesi icin overload edilen fonksiyona cagri yapildiginda derleyicinin n adet fonksiyondan hangisinin cagrilacagini akilli bir sekilde secebilmesi gerekir.

## Function overloading kurallari
Function overloading'den soz edilebilmesi icin iki yada daha fazla fonksiyonun asagidaki ozelliklere sahip olmasi gerekmektedir.
1. Fonksiyon **isimleri ayni** olmali
2. Fonksiyonlar **ayni scope** icinde bildirilmis olmali
   *(Aksi halde [bknz: Scopes ve name-hiding](050_basics.md#scope))*
4. Fonksiyonlarin **imzalari farkli** olmali

----------
> **Fonksiyon bildirimi**
> Bir function asagidaki scopelardan birinde bildirilebilir.
> 1. Block scope
> 2. namespace scope
> 3. class scope
> 
> :warning: 
> Fonksiyonlari parametre turu ve geri donus turu `dizi` ve/ya `fonksiyon turu` olamaz! Ancak fonksiyona yada diziye pointer olabilir. Aksi halde **decay uygulanarak ilgili tur pointer'a donusturulur**.
> 

----------
> **Fonksiyon imzasi**
> Geri donus turu haric tum parametrelerinin sirasi ve turunu ifade eder.
> 
> * Parametre turunun kendisinin `const` olmasi (top-level constness) imzayi **degistirmez**, ancak low-level `const` turu **degistirir**.
> 
> Asagida bildirilen fonksiyonlarin imzalari ayni midir?
> ```C++
> int f1(int, int); 
> int f2(int, double);   // f1 ile imzalari farkli
> double f3(int, int);   // f1 ile imzalari ayni
> int f4(const int, int);// f1 ile imzalari ayni
> ```
> ```C++
> int f1(int*);
> int f2(const int*);    // f1 ile imzalar farkli 
> int f3(int* const);    // f1 ile imzalar ayni
> ```
> ```C++
> int f1(int&);
> int f2(const int&);    // f1 ile imzalar farkli
> ```
----------

* Ayni ture verilen tures isimleri overloading olusturmaz.
* low-level const adres turu ile low-level const olmayan adres turleri arasinda overloading olustusur.
* Ref ile const ref turleri overloading olustururlar.

**Ornekler**
Asagidaki orneklerde function overloading var midir? 

* ```C++
  int foo(int);   // (1)
  
  int main() {
      int foo(double); // (2) degil: scopelari farkli
      
      foo(5);     // Name hiding'den dolayi (2) cagrilir.
      ::foo(5);   // operator:: (1) cagrilir
  }
  ```

* ```C++
  int foo(int);
  double foo(int);    // degil: imzalari farkli olmali
  ```
  Overloading olmadigi gibi gecerli de degil, isimleri ve imzalari ayni olamaz.

* ```C++
  int foo(int);
  int foo(int, int);          // overloading
  double foo(int, int, int);  // overloading
  ```

* ```C++
  int foo(int);
  int foo(int, int = 0);      // overloading var
  ```
  Ancak gecerli degil. Default arg olmasi farkli overload oldugu gercegini degistirmiyor! function overload resolution'da detayli incelenecek.
  

* ```C++
  int foo(int);
  int foo(const int);     // degil: function redeclaration soz konusu
  ```
  Imzalar farkli degil, parametrenin `const` olmasi imzayi degistirmez!
  **function redeclaration**: Ayni fonksiyonun tekrar bildirilmesidir. Function redeclaration kontrolu icin body eklenebilir. Bu durumda redeclaration varsa compiler sentaks hatasi verecektir.
  ```C++
  int foo(int) { return 1; }
  int foo(const int) { return 1; }  
  // syntax error: function 'int foo(int)' already has a body
  ```


* ```C++
  int foo(int * );
  int foo(const int * );  // overloading
  ```
  low-level constness farkli turler olusturur! const overloading: cok sik kullanilan overload turlerinden biridir.


* ```C++
  void foo(double* const p);
  void foo(double* p);    // degil: redecleration
  ```
  top-level constness farkli turleri ifade etmez.


* ```C++
  void foo(int & );
  void foo(const int & ); // overloading
  ```
  En cok kullanilan overloadinglerden biri hemde!


* ```C++
  typedef double flt_type;
  void foo(double);
  void foo(flt_type); // degil, redeclaration
  ```
  Bir ture type-alias olusturmak farkli tur anlamina gelmez.


* ```C++
  void foo(char);
  void foo(signed char);      // overload
  void foo(unsigned char);    // overload
  ```
  `char`, `unsigned char`, `signed char` tur sistemi icinde farkli *distinct* turlerdir.

* ```C++
  void foo(int*);
  void foo(int**);   // overload
  void foo(int***);  // overload 
  ```
  `int*`, `int**`, `int***` tur sistemi icinde farkli turlerdir.
  
  
* ```C++
  void foo(int&);
  void foo(int&&);      // overload
  void foo(const int&); // overload
  ```
  `T&`, `T&&` ve `const T&` ayri turlerdir. `const int&` low-level const, farkli bir tur olusturur!
  
* ```C++
  #include <cstdint>  // std::int32_t
  
  void foo(std::int32_t);
  void foo(int);      // Overloading var yada yok denilemez
  ```
  Derleyiciye bagli olarak, `std::int32_t` hangi ture alias oldugu degisebilir.
  Eger `int`'e alias ise redeclaration, `int` disinda baska bir ture alias ise overloading.

* ```C++
  void foo(std::int32_t);
  void foo(std::int16_t); // overloading
  ```
  Standartlara gore ayni turde olmasi mumkun degildir.
  
  
* ```C++
  void foo(int);
  void foo(int *);    // overloading
  ```

* ```C++
  void foo(int);
  void foo(int &);    // overloading
  ```

* ```C++
  void foo(int p[]);
  void foo(int p[20]);    // redeclation
  void foo(int *p);       // redeclation
  ```
  Bir fonksiyon parametresi dizi olamayacagi icin derleyici bildirimlerde kullanilan array tanimlarina **array-decay** uygular.
  Bu durumda `int p[]`, `int p[20]` ile `int* p` aynidir.

* ```C++
  void foo(int(int));
  void foo(int(*)(int));  // redeclaration
  ```
  `int(int)` bir function type, `int(*)(int)` bir function pointer type. Fonksiyonun parametresi dizi olamadigi gibi fonksiyon da olamaz. Derleyici burada **function-decay** uygular.
  
* ```C++
  void foo(int (*)[5]);   // overload: 5 elemanli dizi ptr turu
  void foo(int (*)[6]);   // overload: 6 elemanli dizi ptr turu
  void foo(int (*)[7]);   // overload: 7 elemanli dizi ptr turu
  void foo(int (*)[8]);   // overload: 8 elemanli dizi ptr turu
  ```
  Oyle bir pointer tanimi yapilsin ki dereference edildiginde ifade `int[5]` dizisinin kendisi anlamina gelsin:
  ```C++
  int (*ptr)[5];
  ```
  ```C++
  int a5[5] {};   //
  int a6[6] {};   // bunlarin her biri ayri bir tur
  int a7[7] {};   //
  
  int(*p1)[5] = &a5;  // int[5] turunden bir dizinin adresini ifade eden bir pointer
  int(*p1)[6] = &a5;  // sentaks hatasi: tur uyusmazligi
                      // &a5, &a6, &a7 farkli turden adresler
  
  void foo(decltype(&a5));  
  void foo(decltype(&a6));  //  bu nedenle 3 adet overloading var!
  void foo(decltype(&a7));
  ```










<!--  -->

--------------

> :warning: 
> **Genellikle yanlis ogrenilen yada cok yapilan hatalar**  
> 1. Ayni isimli yanlis fonksiyonun cagrilmasi
> 2. Ortada (kodda) bir function overloading var mi yok mu?
> 3. Function overloading ve function overload resolution birbiri ile karistirilmasi
>    Function overload resolution cagrilan bir fonksiyonun hangi overload'unun cagrildigi ile ilgilenirken function overloading fonksiyon bildirimi ile ilgilidir.
>    Yani function overload resolution yapilan cagriya gore degisirken, function overloading fonksiyon tanimlarina gore degisir.

[Calisma Sorulari](hw/140_function_overloading/)