# C ve C++ Farkliliklar
*C dilinde gecerli ancak C++ dilinde gecerli olmayan temel farkliliklar*

* [C99] standartları ile C diline eklenen bazı araçlar C++ dilinde bulunmamaktadir. _(restrict pointers, compound literals, flexible array members, designated initializers...)_

* C dilinde bulunan `auto` anahtar sözcüğü ile C++'da bulunan `auto` farklı anlamlarda kullanılmaktadir.  
  C'deki `auto` anahtar sozcugu degiskenin [otomatik omurlu](050_basics.md#automatic-storage) bir degisken oldugunu ifade etmek icin kullanilir. C++'da [type deduction](110_type_deduction.md#auto-type-deduction) amaciyla kullanilir.

> **DIKKAT!**  
> C ve C++ dillerinde en tehlikeli durumlardan biri **yanlislikla yazilan bir kodun ayni zamanda sentaks kurallari cercevesinde gecerli oldugu** durumlardir.

* C dilinde statik tur kontrolu daha esnektir. Bazi farkli turler arasindaki atama ve kopyalama islemleri gecerli olmasa da sentaks olarak gecerlidir. C++ dilinde cok daha siki bir kontrol bulunmaktadir.

* **implicit int** C dilinde fonksiyon geri donus turu acikca belirtilmemis ise geri donus turu ortulu olarak `int` kabul edilir. C++ dilinde bu kullanim sentaks hatasidir.
  ```C++
  func(double dval);     // func = int func(double);
  ```

* **implicit function declaration** C dilinde olan _"default function declaration" (implicit function declarations)"_ yoktur. C++ dilinde tüm isimler _(identifiers)_ bildirilmelidir. Isim arama basarisiz olursa sentaks hatasi uretilir.

* **function overloading** C dilinde iki fonksiyon ayni isme sahip olamaz, C++ dilinde belirli kurallar cercevesinde ayni ismi paylasan fonksiyonlar bir arada bulunabilir.

* C dilinde fonksiyon bildirimlerinde fonksiyon parametresinin `void` olmasi ile bos birakilmasi arasinda kural farkligi bulunmaktadir. C++ dilinde bu kural farkliligi bulunmamakta ve parametre degiskeni yok anlaminda kabul edilmektedir.
  ```C
  // C dilinde
  int foo();     // foo fonksiyonun parametre degiskeni yok demek degil, bilgi verilmiyor demektir.
  int bar(void); // bar fonksiyonun parametre degiskeni yok demektir
  ```

* C dilinde fonksiyon taniminda parametre degiskenine isim verilmesi zorunludur. C++ dilinde zorunlu degildir.
  ```C++
  void func(int)    // C'de sentaks hatasi, C++'da gecerli
  {
  }
  ```
  *Function overloading'de farkli imzalar olusturulabilmesi icin faydalanilabilmektedir.*

* `for` dongusunde bildirilen degiskenler C dili kurallarina gore dongu blogunu kapsayan ancak dis blogu kapsamayan ayri bir blok icinde tanimlanmis kabul edilir. C++ dilinde bu kural bulunmamaktadir. Dolayisiyla ayni blok icinde ayni isme sahip birden fazla oge olmasi nedeniyle sentaks hatasidir.
  ```C++
  for(int i = 0; i < 10; ++i) {
    int i = 99;         // C dilinde gecerli, C++ dilinde sentaks hatasi
    printf("%d", i);    // name-hiding nedeniyle 99 yazdirir
  }
  ```

## Turlere ve tur donusumlerine iliskin farkliliklar

### bool turune iliskin farkliliklar

* C dilinde C99'a kadar logic bool turu bulunmamaktadir ve yerine `signed int` turu kullanilmaktadir.
  
  C99 ile `_Bool` turu `stdbool.h` icinde tanimlanarak *basic type* olarak eklenmistir, ancak `true` ve `false` boolean sabitleri bulunmamaktadir. Bunun yerine makro olarak tanimlanmislardir:
  ```C++
  #define bool _Bool
  #define false 0
  #define true 1
  ```
  **Ornek**
  ```C
  // C
  _Bool flag = true; // signed int flag = 1;
  ```
  C++ dilinde `bool` turu herhangi bir baslik dosyasi eklenmeden kullanilabilen storage ihtiyaci 1 byte olan bir primitive turdur. `bool`, `true` ve `false` anahtar sozcuklerdir. 
  ```C++
  // C++
  bool flag = true;
  flag = false;
  ```

* C dilinde karşılaştırma operatörleri ve lojik operatörler `signed int` turunden `1` ve `0` değerlerini üretmektedirler. C++'da `bool` türünden `true` ya da `false` değerlerini üretiyorlar.

* [C++17] ile `bool` turunden bir degiskenin `++` ve `--` operandi olarak kullanilmasi dilden kaldirilmistir.
  
* C ve C++ dilinde aritmetik turlerden `bool`'a ortulu donusum **gecerlidir**.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  int x = 45;
  int y = 0;
  bool flag1 = x;    // flag1 = true
  bool flag1 = y;    // flag2 = false
  ```
  ```C++
  bool flag1 = true;
  bool flag2 = false;
  
  int x = flag1;    // x = 1
  int y = flag2;    // y = 0
  ```
  </details>
  <!--  -->
  
* Adres turlerinden bool turune ortulu donusum gecerlidir. Ancak bool turunden adres turlerine ortulu donusum sentaks hatasidir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  int* g_ptr;
  
  int main()
  {
    int x = 100;
    int* ptr = &x;
    bool bval1 = ptr;   // bval1 = true
    bool bval2 = g_ptr; // bval2 = false
  }
  ```
  ```C++
  bool flag = true;
  int* ptr = flag;      // sentaks hatasi
  ```
  </details>
  <!--  -->

### Karakter sabitlerine iliskin farkliliklar

* C dilinde karakter sabitlerinin _(character literals)_ türü `int`, C++ dilinde ise `char`dir.
  ```C
  printf("%zu", 'A'); // C'de 4, C++'da 1
  ```
  *C++ dilinde `int` ve `char` turleri farkli turler olarak ele alinmaktadir.*

* C dilinde string literallerinin turu `char` turunden dizilerdir. C++ dilinde `const char` turunden dizilerdir.
  C dilinde string literalleri `char*` turune, C++'da `const char*` turune decay olur.  
  C++'da `char*` türünden değişkenlere string literalleri ile ilk değer verilemez ya da atama islemi yapilamaz.
  ```C++
  const char* p1 = "akif";  // C/C++ gecerli
  char* p2 = "akif";        // C'de gecerli, C++'da gecersiz
  ```
  > **DIKKAT!**  
  > Her iki dilde de string literalini degistirme islemi **UB**'dur.  
  > Her iki dilde de `const char*` kullanilmasi tanimsiz davranis durumundan kacinmak icin iyi bir uygulamadir.

* C dilinde dizi boyutu ile ilk değer veren string literalinin karater sayısı *null terminator haric* eşit ise tanım *(definition)* geçerlidir. C++'da sentaks hatasidir.
  ```C++
  char str[4] = "anil"` // C'de geçerli, C++'da gecersiz
  ```
  C dilinde gecerli ancak **tehlikeli**, null-terminated string beklenen bir yerde kullanilir ise **UB**.

### Array turlerine iliskin farkliliklar
* C dilinde bir diziye ilk deger verilirken `{}` ici bos birakilmasi sentaks hatasidir. C++'da gecerlidir ve zero-initialize edilir.
  ```C++
  int a[4] = {};  // C'de gecersiz, C++'da gecerli
  ```
* C diline C99 standartlari ile eklenen *designated initializer*, C++20 standartlarina kadar dilde bulunmuyordu.   
  *C++20 ile eklenen designated initializer sentaksi ile C dilindeki sentaks tamamen farklidir.*
  ```C++
  int a[100] = { [3] = 5, [17] = 9};  // C dilinde gecerli, C++20'de gecersiz
  ```

### User-defined turlere iliskin farkliliklar

* C dilinde programci tarafindan olusturulan türleri _(user-defined types)_ (`struct`, `union`, `enum`, `class`)  nitelenirken etiketleri _(tag)_ ile birlikte kullanılması zorunludur. C++ dilinde etiketleri _(tags)_ doğrudan türü niteleyen isimler olarak kullanılabiliyor.
  ```C++
  struct Data {
    int a, b, c;
  };
  ```
  ```C++
  Data m_data;          // C'de gecersiz, C++'da gecerli
  struct Data m_data2;  // C'de ve C++'da gecerli
  ```
* C dilinde user-defined bir tur en az bir öğeye sahip olması zorunludur. C++ dilinde, ogesi bulunmayan turler *(empty class)* tanimlanabilmektedir.
  ```C++
  struct Data{};        // C'de gecersiz, C++'da gecerli
  ```

* C dilinde tur es isimler sadece `typedef` bildirimi ile yapilabilirken, C++ dilinde `using` bildirimi ile de yapilabilmektedir.
  ```C++
  typedef int WORD;   // C ve C++'da gecerli
  using WORD = int;   // Sadece C++
    
  typedef int(*FCMP)(const void*,const void*);    // C ve C++'da gecerli
  using FCMP = int(*)(const void*,const void*);   // Sadece C++
  ```

* C dilinde *out-of-order designated initialization*, *nested designated initialization*, *designated initializers* ve *regular initializers* birlikte kullanimi desteklenmektedir, fakat C++ dilinde sentaks hatasidir.
  ```C++
  struct A { int x, y; };
  struct B { struct A a; };
   
  struct A a = {.y = 1, .x = 2}; // valid C, invalid C++ (out of order)
  struct B b = {.a.x = 0};       // valid C, invalid C++ (nested)
  struct A a = {.x = 1, 2};      // valid C, invalid C++ (mixed)
  ```

### `const` anahtar sozcugune iliskin farkliliklar

* C dilinde `const` olarak tanimlanmis primitive bir ogeye ilk deger verilmesi zorunlu degildir. C++ dilinde ilk deger verilmesi zorunludur, aksi halde sentaks hatasi uretilir.
  ```C++
  const int x;    // C'de gecerli, C++'da gecersiz
  ```
  
* C dilinde `const` olarak tanimlanmis nesnelerin olusturdugu ifadeler sabit ifadesi *(constant expression)* olarak degerlendirilmemektedir. C++ dilinde ilk değerini sabit ifadesi ile almış `const` nesnelerin oluşturduğu ifadeler sabit ifadesi olarak ele alınmaktadir.
  ```C++
  const int x = 10;
  int a[x] = { 0 };   // C dilinde gecersiz, C++'da gecerli
  ```
  ```C++
  int get_size();
  
  const int size = 100;
  const int ds = get_size();  // sabit ifadesi gereken yerde kullanilamaz, cunku degerini degisken ifadesi ile almis
  
  int a1[size];   // gecerli
  int a2[ds];     // gecersiz
  ```

* C dilinde sadece `const` anahtar sozcugu bulunmaktadir. C++'da `const`a ek olarak `constexpr` vs `consteval`[C++20] anahtar sozcuklari ile daha zengin bir const semantigi bulunmaktadir.

* C dilinde global `const` nesneler varsayilan olarak **external linkage** iken, C++ dilinde varsayilan olarak **internal linkage** olarak ele alinir.  
  ```C++
  const int x; // C'de external, C++'da internal
  ```
  *C'de bir global degiskenin `const` olmasi baglanti ozelligini degistirmemektedir.*

* C dilinde `const T*` turunden `T*` turune ortulu donusum yanlis olmasina ragmen dil kurallarina gore gecerlidir. C++'da sentaks hatasidir.  
  ```C++
  int i = 10;
  const int ci = 10;
  
  &i;   // &i = int*
  &ci;  // &ci = const int*
  
  int* p = &ci; // C'de gecerli, C++'da degil.
  ```
  Asagidaki kod ornegi C dilinde `const T` turunden bir nesnenin adres turu `const T*` olmasina ragmen `T*` turune ortulu donusum gerceklestirilebilecegi icin gecerlidir:
  ```C++
  const int x = 10;
  int* p = &x;   // C'de (yanlis ama) gecerli, C++'da gecersiz
  ```

### Pointer turlerine iliskin farkliliklar

* C dilinde aritmetik turler ile adres turleri arasinda ortulu donusum gecerlidir, C++'da sentaks hatasidir.
  ```C++
  int x = 35;
  int* p = x; // C dilinde x int'den int* donusur, C++ da gecersiz
  ```

* C dilinde farkli adres turleri arasinda (`T` ve `U` farklı türler olmak üzere `T*` türünden `U*` türüne) örtülü dönüşüm gecerlidir, C++'da *istisnalar haric* sentaks hatasidir.
  ```C++
  double dval = 3.5;
  char* p = &dval; // C dilinde x int'den int* donusur, C++ da gecersiz
  ```

* C dilinde `T` bir `void` olmayan bir tür olmak üzere `void*` türünden `T*` türüne örtülü dönüşüm gecerlidir. C++ dilinde sentaks hatasidir.
    ```C++
  size_t n = get_size();
  int* p1 = malloc(n * sizeof(int));           // C'de gecerli, C++'da gecersiz.
  int* p2 = (int*) malloc(n * sizeof(int));    // C ve C++'da gecerli
  ```

### Enum Turlerine iliskin farkliliklar

* C dilinde bir `enum` turu icin **underlying type** `int` olmak zorundadir. C++'da farkli turler underlying type olarak bildirilebilmektedir. 
  ```C
  // C dilinde
  enum Color { While, Gray, Black };
  assert(sizeof(enum Color) == sizeof(int));    // C dilinde her zaman gecerli
  ```
  ```C++
  // C++ dilinde
  enum Color : unsigned char { While, Gray, Black };
  ```

* C dilinde aritmetik türlerden `enum` türlerine örtülü dönüşüm gecerlidir. C++ dilinde sentaks hatasidir.
  ```C++
  enum Color mycolor;
  mycolor = 3;  // C'de gecerli, C++'da gecersiz
  ```

* C dilinde farklı `enum` türleri arasında örtülü dönüşüm gecerlidir. C++ dilinde sentaks hatasidir.
  ```C++
  enum Color my_color;
  enum Pos my_pos = Off;
  my_color = my_pos;    // C'de gecerli, C++'da gecersiz
  ```

* C dilinde de C++ dilinde de `enum` turlerinden aritmetik turlere donusum gecerlidir.  
  *C++'in genclik gunahlari*
  ```C++
  enum Color my_color = Black;
  int x = my_color;     // C/C++ gecerli
  ```
  > **DIKKAT!**  
  > C++'da bu donusum [scoped enum](130_scoped_enum.md) icin gecerli degildir.

## Deger kategorine iliskin farklar

* C dilinde bir ifade `lvalue` veya `rvalue` deger kategorilerinden birine aittir. C++ dilinde bir ifade primary olarak `lvalue`, `prvalue` yada `xvalue` kategorilerinden birine aittir.

* Aritmatik ifadelerden ve sabitlerden olusturulan degerler tipik olarak `rvalue expr`'dir.

+ C dilinde *rvalue expression* olan bazı ifadeler C++ dilinde *lvalue expression* deger kategorisindedir.  
    
  | expression |   C   |       C++       |
  | ---------- | :---: | :-------------: |
  | x          |   L   |        L        |
  | +x         |   R   |        R        |
  | ++x        |   R   |        L        |
  | --y        |   R   |        L        |
  | (a, b)     |   R   | (duruma gore) L |
  | ? :        |   R   | (duruma gore) L |
  | assignment |   R   |        L        |

  *_[value category](065_value_categories.md)_ kurallarında iki dil arasında kural farklılıkları bulunmaktadir.*
  
> **Not**  
> (C icin) Bir ifadenin rvalue yada lvalue oldugunu anlamadiginizda adres operatoru `(&)`'nun operandi yapin.

## Baslik dosyalarina iliskin farklililar

C dilinin standart kutuphanesi C++ dilinin standart kutuphanesinin bir bilesinidir.

C dilinden gelen bir standart kutuphane baslik dosyasini C++ dilinde kullanilirken `.h` uzantisi yerine `c` prefixi kullanilir.
```C++
// C++              //  C
#include <cstdio>   // #include <stdio.h>
#include <cstring>  // #include <string.h>
#include <cctype>   // #include <ctype.h>
```
Bu baslik dosyalari C++'in bazi araclarina uyumluluk saglayabilmek amaci ile olusturulmustur.

C dilinde tum fonksiyon bildirimleri global isim alaninda bulunur. Farkli dosyalardan gelen ayni isimli ogeler cakismaya neden olmaktadir.

C dilinde derlenmis bir fonksiyon isminin [mangle](#TODO:#name-mangling) edilmesi ile C++'da mangle edilmesi dillerin farkli arac setlerine destek vermesi nedeniyle birbirinden farklidir.

## C dilinde genel kabul gormus ancak C++ dilinde uygulanmasi tavsiye edilmeyen bazi aliskanliklar:

* Bir fonksiyonun ana blogu basinda kullanilacak tum degiskenlerin tanimlanmasi
  ```C++
  void func()
  {
    int a, b;
    // ...
    double x, y;
    
    // statments
  }
  ```
  C89'da zorunluluk, C99'da kaldirilan, C dilinin klasik donemlerinde kalma bir kodlama bicimidir.
  Tavsiye edilen; [scope leakage](999_kavramlar.md#scope-leakage) olusturmadan, kullanildigi ilk yerde bildirilmesidir.

