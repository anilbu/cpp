
# Basic Types
*Fundamental types/built-in types/primitive types*

Dil tarafindan hazir olarak saglanan, user-defined olmayan turlerdir.

## Tam sayi turleri

| type                                           |        sizeof         |      suffix      | Expression |
| ---------------------------------------------- | :-------------------: | :--------------: | :--------- |
| `bool`                                         |           1           |                  |            |
| `char`<br/> `signed char`<br/> `unsigned char` |           1           |                  |            |
| `short`<br/> `usinged short`                   |                       |                  |            |
| `int`<br/> `unsigned int`                      | 2/*4/8 <br/> impl-def |      <br/>U      |            |
| `long`<br/> `unsigned long`                    |       >= 8 byte       |   L<br/>UL/LU    |            |
| `long long`<br/> `unsigned long long`          |       >= 8 byte       | LL <br/> ULL/LLU |            |
  
* C++'da primitive turler class degildir.
* `int` turu boyutu icin tipik olarak islemcinin **WORD** uzunlugu kullanilir.
* `signed`/`unsigned` tur belirtilmeden kullanildiginda `int` turunu ifade eder.
* `char` turu haric bir primitive tur `signed` yada `unsigned` olarak belirtilmediginde `signed` bir turu ifade etmektedir.
* Tum derleyiciler asagidaki ifadeye uymak zorundadir:
  ```C++
  sizeof(short) <= sizeof(int) <= sizeof(long) <= sizeof(long long)
  ```
* [C++20] Standart olarak negatif sayilaring gosterimi [**2's complement**](999_kavramlar.md#2s-complement-taktigi) olmasi garanti altindadir.

* Eger literal belirtec kullanilmadan (orn LL) `int` sayi sinirlarini asan bir deger ile ifade ediliyor ise hangi ture sigacagina bakilarak turu tespit edilir. 
  ```C
  // int'e sigmadigi icin long olur
  329'200'0123;
  ```

* Isaret operatoru `+` ve `-` sabit ifadesine dahil degildir.
  ```C++
  -23;            // sabit ifdes = 23
  -2147483648;    // long long, unsigned int degil
  ```
  2147483648 ifadesi degeri `int` turune sigmaz. Isaret, sabit sayi ifadesinden ayri olmasi nedeniyle `unsigned int` turune sigmasina ragmen `long long` olur. Bu durum derleyiciye *int kac byte olduguna* gore degisir.

## Gercek sayi turleri

| type          |  sizeof  | suffix | Expression |
| ------------- | :------: | :----: | :--------- |
| `float`       |    4     |   F    | 4.5F       |
| `double`      |    8     |        | 4.5        |
| `long double` | impl-def |   L    | 4.5L       |

* [IEEE758](https://en.wikipedia.org/wiki/IEEE_754) formati
* `double` yerine `float` kullanimi; hassasiyetin onemli olmadigi, memory'nin onemli oldugu durumlarda kullanilmalidir.

## `const` anahtar sozcugu

```C++
const int x = 10;
```

* `const` anahatar sozcugu ile tanimlanan bir degisken **[immutable](020_temel_kavramlar.md#terminoloji)**dir. 
* `const` anahtar sozcugu ile bildirilen degiskenler default initialize edilemiyorlar, ilklendirilmeleri zorunludur. Ilklendirme ifadesinin `constexpr` olmasi zorunlu degildir.
  ```C++
  int foo();
  const int x = foo();
  ```
* `const` bir degisken ilklendirmesini bir `constexpr` bir ifadeden almis ise kendisinin olusturdugu ifade bir `constexpr`dir, aksi halde constexpr degildir.
  ```C++
  const int x = 10;
  const int y = 20;
  const int z = 30;
  int a[x + y + z];     // x, y, z ve x+y+z ifadeleri birer constexpr'dir
  ```
  ```C++
  int foo(void);
  
  const int w = foo();
  int a[w];     // sentaks hatasi: w ifadesi bir constexpr degildir.
  ```

* `const` ayri bir tur olusturur.
  ```C++
  const int x = 10;
  decltype(x) y;              // y = const int
  ```

> :warning: 
> Derleyici `constexpr` veya `const` degiskenler icin bellekte yer ayirmak zorunda degildir. Ancak degiskenin **adresine erisim** varsa yer ayirmak zorunda kalir.

### Fonksiyon parametrelerinde `const` semantigi
```C++
void func(std::string &);
void func(const std::string &);

void func(std::string *);
void func(const std::string *);
```
Eger fonskiyonun parametresi pointer yada ref degilse, `const` kullanilmasi yeni bir imza olusturmuyor!
```C++
void func(int);
void func(const int);   // overload degil, redeclaration
```
Ayrica parametrenin `const` olup olmamasi, fonskiyonu cagiran icin herhangi bir fark olusturmuyor. Cunku call-by-value olarak cagrilacagi icin deger kopyalanir.
Fonksiyon definition'da const bir parametre fonksiyon blogunda degeri degistirilmiyor anlamina gelmektedir.

Fonksiyon bildiriminde asla `const` u kullanmayin. Eger gerek goruluyor ise tanimda kullanilabilir.
```C++
// lib.h
void func(int x);
void func(int* ptr);

// lib.cpp
void func(const int x)
{
}

void func(int* const ptr)
{
}
```



# Sayi Sistemleri

| Number System | Base  | Prefix | Expression | Value |
| ------------- | :---: | :----: | :--------- | :---- |
| binary (C++)  |   2   |   0b   | 0b00101001 | 41    |
| octal         |   8   |   0    | 041        | 33    |
| decimal       |  10   |        | 41         | 41    |
| hexadecimal   |  16   |   0x   | 0x41       | 65    |

* Varsayilan olarak kullanilan sayi sistemi `decimal`dir.
* Kullanilan sayi sistemine gore literalin turu degisebilir.
  ```C
  // unsigned int, cunku hex olarak ifade edilmis
  0x8000'0111;
  ```

# Initialization
## Default Initialization
Bir degisken olusturulurken ilk deger verilmeden olusturulmasidir.
```C++
int x;      // default initialization (garbage value if non-static)
```
* Otomatik omurlu degiskenler, default initialization cop deger *(garbage value)* ile initialize edilmektedir. Garbage value ile initialize edilmis bir degerin kullanimi **UB**'dir.
* Statik omurlu degiskenler *(global, static yerel, string literalleri)*, default initialize edildiginde **zero initialize** edilir.

* `const` nesneler default initialize edilemezler.
* Referans turunden nesneler default initialize edilemezler.

## Copy Initialization
Bir degisken olusturulurken verilen bir degerden kopyalanarak olusturulmasidir.
```C++
int x = 0;  // copy initialization
```

## Direct Initialization
Bir degisken olusturulurken verilen bir deger ile olusturulmasidir.
```C++
int x(0);   // direct initialization
```

## Uniform Initialization
*Brace initialization/direct-list initialization*
```C++
int x{ 0 };   // uniform/brace/direct-list initialization
```
**Neden Modern C++'a `{}` ile initialization eklendi?**  
1. Herhangi bir degiskene ilk deger vermenin **uniform bicimde** olusturulabilmesi
2. Ortulu tur donusumlerinde [narrowing conversion](060_type_conversions.md) olusmasi durumunda **sentaks hatasi** uretilebilmesi
3. Bazi bildirimlerde [most verxing parse](999_kavramlar.md#most-vexing-parse) durumlarindan kacinilanabilmesi

## Value Initialization
Bir degiskenin olusturulurken zero-initialize edilerek olusturulmasidir.
```C++
int x{};    // value initialization (once zero-initialization)
```
Kavramsal olarak `{}` ile `{0}` birbirinden farkli initialization bicimleridir.

**Zero initialization kurallari**  
```C++
bool bval{};     // bval = false
int ival{};      // ival = 0
int* ptr{};      // ptr = nullptr
```
* `bool` turunden degiskenler `false` degeri ile 
* Aritmetik turunden degiskenler `0` degeri ile 
* Adress turunden degiskenler `nullptr` degeri ile 

> :triangular_flag_on_post: 
> Global degiskenler default initialize edildiginde once zero-initialize edilir.  
> Aritmetik turler value initialize edildiginde once zero-initialize edilir.

## Dizi turlerinin ilk deger almasi
Asagidaki bildirimlerin hepsi aynidir ve **zero-initialize** edilir.
```C++
int a1[4] = {0};
int a2[4] = {};
int a3[4]{};
```

## Aggregate Initialization
Initializes an aggregate from an initializer list.
```C++
struct Nec {
  int a, b, c;
};
  
Nec nec = { 1, 5, 7};   // aggregate initialization
```
```C++
struct Nec {
    int ar[5];
};

Nec nec = { 1, 5, 7};   // aggregate initialization
```
**Aggregate type**  
Bir dizi turu yada bazi ozelliklere sahip sinif turleridir.  

Bir sinif turunun aggregate tur olabilmesi icin:
* user-declared yada inherited constructor'a sahip olmamali
* private yada protected non-static data member'a sahip olmamali
* virtual base class'dan kalitima sahip olmamali
* private yada protected base class'dan kalitima sahip olmamali
* virtual member function'i olmamali

# Expressions

Bir ifade sabitlerin, degiskenlerin, operatorlerin bir araya getirilerek olusturuldugu birimlerdir. Bir ifade alt ifadelerden *(subexpression)* olusabilir. 

```C++
10
x
x + 5
f(x)
f(x) > g(x)
++x
x++
x * x + y * y + z * z
```

Her ifadenin bir **data type**'i ve bir **value category**'si bulunmaktadir.

> :warning: 
> Bildirilen isimlerin bir value categorysi yoktur, expressionlarin vardir.

## Constant Expression
Degeri compile-time'da *-derleyici tarafindan-* bilinen ifadelere **constant expression** denir.  

**C'de constexpr kullaniminin zorunlu oldugu yerler:**  

+ Dizi boyutu gosteren ifadeler (variable len arr haric)  
  ```C 
  int a[constant expression];
  ```
+ Global vars'in initialize degerleri
  ```C 
  int x = 10;
  int y = x + 5; // C'de hata, C++'da gecerli
  ```
+ `case` ifadeleri *(switch/case)*
+ Bitfield member
  ```C
  struct nec{
    int x : 5; // 5 ifadesi constexpr olmalidir
  };
  ```

[[bknz: constexpr anahtar sozcugu](170_constexpr.md)]

# Scope 
*Kapsam*  

Scope, isimleri niteleyen bir terimdir. C++'da bildirilen bir isim bir scope ait olmalidir.

<!-- 
C'de scope kategorileri:
* Block scope
* File scope
* Function prototype scope
* Function scope 
-->

**C++'da scope kategorileri**
* Block scope
* namespace scope
* class scope
* Function prototype scope
* Function scope

> :warning: 
> C'de ve C++ dillerinde scope kurallari ve kategorileri birbirinden farklidir.

**Kurallar**  
* Ayni scope'da ayni ismin birden fazla varliga verilmesi **sentaks hatasi**dir.
* Farkli scopelarda tanimlanan ayni isimlerin, kendisini kapsayan (enclosing) scopedaki ismileri gizlemesine **name-hiding** (name masking/name shadowing) denilir.
* Fonskiyon parametre degiskenlerinin scope'u tanim bloguna aittir.
  ```C++
  void func(int a) {
    int b;
  }
  ```
  *`a` ve `b`nin scopelari aynidir:*
  
## Unary `::` scope resolution operatoru
Sadece C++'da var, hem unary hemde binary bir operatordur. Unary olarak kullanildiginda bu ismi global scope'da ara anlamina gelmektedir.

Unary `::` operatoru kullanildiginda operand isim icin isim arama global scope'da yapilir.

```C++
void x();

int main() {
  int x = 34;     // name-hiding
  std::cout << x; // local'de tanimlanan x degiskenidir.
  ::x();          // global'de tanimlanan x fonskiyonudur.
}
```

# Storage Duration
*storage duration*

Storage class, bir nesnenin o nesne icin ayrilmis yada ayrilacak olan bellek alaninda hangi sure ile duracagini belirtir.

> :warning: 
> *Scope* kavrami isimlerin *(identifiers)* niteligidir, *storage class* ise nesnelerin niteligidir.

## Automatic storage
Kodun yurutulmesi suresince bellekte kalan degiskenlerdir. Compile-time'da belirlenir.
Tipik olarak `stack`de barindirilir.

## Static storage
Hayata geldikten sonra kaybolmayan nesnelerin storage turudur. Compile-time'da belirlenir.
Tipik olarak `.data segment`inde barindirilir.

1. Global variables
2. static local variables
3. String literal karsiligi derleyicinin olusturdugu char diziler

> :triangular_flag_on_post: 
> Global nesneler hayata main fonksiyonu cagrilmadan once gelir.  
> Statik lokal degiskenler, bulundugu fonksiyon ilk kez cagrildiginda hayata gelmektedir.

## Dynamic storage
Hayata gelmesi/yok edilmesi programci tarafindan belirlenmis nesnelerin storage turudur. Runtime'da belli olur.
Tipik olarak `heap`'de barindirilir.

##  Thread-local storage
<!-- TODO -->


# Name lookup
*Isim arama*  

Derleyicinin derleme sureclerinden biridir. Derleyicinin kodu derleyebilmesi icin oncelikle tokinizing sirasinda isim *(identifiers)* olarak tespit ettigi ifadelerin hangi varliklara ait oldugunu anlamasi gerekmektedir. Name-lookup sonucu "bu isim neyin ismi" sorusuna cevaptir. Dilin kurallari ismin hangi kod alanlarinda hangi sira ile yapilacagini belirlemektedir.

Isim aramanin **altin kurallari**:
1. Isim arama dilin kurallarinca belirlenmis bir siraya gore yapilir.
2. Aranan isim bulundugunda, isim arama sureci sonlanir. Isim aramasi yapilmis bir ifade icin tekrar isim arama baslatilmaz.

<!-- 
C dilinde isim arama 2 sekilde sonlanabilir:
1. Aranan isim bulunamaz (Undefined idef.)
2. Aranan isim bulunur ve sonraki surece gecilir 
-->

**C++ dilinde isim arama 3 sekilde sonlanabilir:**
1. Aranan isim bulunamaz (Undefined identifier)
2. Aranan isim bulunur ve sonraki surece gecilir
3. Ambiguity

> **Ambiguity** Birden fazla secenek olmasina ragmen seceneklerin kendi arasinda bir secim kriterinin olmamasi durumu.

[Soru 21](res/sorular/soru21.cpp)  
[Soru 22](res/sorular/soru22.cpp)  

**Ornek**
* UB'dir. Cunku once isim arama yapilir.
  ```C++
  int x;
  
  int main() {
      int x = x;
      std::cout << x << std::endl;
  }
  ```
* Asagidaki iki program gecerli midir? Programlarin ciktisi nedir?
  ```C++
  int main(void)
  {
      int printf = 5;
      printf("Merhaba dunya");
  }
  ```

# Fonksiyonlar
<!-- TODO -->

* Global (free) yada bir member function, bir sinifi parametrik olarak aliyorsa sunlardan biri olmak zorunda:
  1. mutator: Nesnesinin degerini degistirmeye yonelik
    ```C++
    void func(T *);         // mutator
    void func(T &);         // mutator
    ```
  2. accessor: Nesnesinin degerini kullanmaya yonelik
    ```C++
    void func(const T *);   // accessor
    void func(const T &);   // accessor
    ```

```C++
void func1(T *p);         // out param (mutator function)
void func2(T *p);         // in-out param
void func3(const T *p);   // in param
```

## Variadic functions
<!-- TODO -->

```C++
void func(int, ...);
```
Tipler variadic conversion ile tespit edilir.
```C++
func(1);
func(1,4,5);
```

## deleted functions
Fonksiyon bildirimi yapilmis ve bu fonksiyona cagri yapilmasi sentaks hatasisi olusturmasi istendiginde fonksiyon delete edilebilmektedir.
```C++
void func(int) = delete;
```
```C++
func(12); // hata!
```
> :warning: 
> Fonksiyonun hic bildirilmemis olmasindan farki, delete edilmis bir fonksiyon function overload resolution'da yine aday ve viable fonksiyonlardan biri olmasidir. Argumanlarin implicit donusumunu engellemek icin kullanilabilir.
```c++
void func(double);            // (1)
void func(float);             // (2)
void func(int)  = delete;     // (3)
```
```C++
func(2.4f);   // (1) secilir ve cagrilir
func(2.4);    // (2) secilir ve cagrilir
func(3);      // (3) secilir ancak cagrilamaz, sentaks hatasi verir.
```

# Operatorler

Operatoreler operand sayisina gore nitelendirilir. 
* unary
* binary
* ternary

Operatore konumlari:
* prefix: ++x yada *ptr  
* postfix: x++
* infix: a + b

<p align="center">
<img src="res/img/op_pred.png"/><br/>
Sekil: Operator oncelik tablosu
</p> 

> :triangular_flag_on_post: 
> Operatorler konusunda bu dokumanda en cok yapilan hatalara yonelik aciklamalar bulunmaktadir.

## `sizeof` operatoru
Operandi olarak verilen ifadenin storage ihtiyacini ureten bir operatordur.

* `sizeof` anahtar sozcugu bir operatordur, bir fonksiyon degildir.
* `sizeof` operatoru ile olusturulan ifadeler **constant expression**dir. Yani compile-time sabitidir.
* Urettigi deger `size_t` turundendir. `size_t` turu derleyici implementasyonuna gore degisebilir.
  > :warning: 
  > Tur donusumu kurallari geregi, isaretli ve isaretsiz bir tur arasinda islem yapilacagi zaman tur donusumu isaretsiz olan yone yapilir!  
  > ```c++
  > int x = 0, ival = -5;
  > if(sizeof(x) > ival)   // sizeof(x) 4u olmasi nedeniyle true olur!
  > ```
* `sizeof` operatorunun **onceligi** aritmetik operatorlerden daha **yuksektir**.
* `sizeof` operatorunun operandi olan ifade **unevaluated context** oldugu icin islem kodu uretilmez. 
  ```C++
  int x = 10;
  size_t y = sizeof x++;    // x++ ifadesi icin islem kodu uretilmez!
  printf("%zu %d", y, x);   // y = 4, x = 10
  ```
  C dilinde cok kullanilan bir idiom:
  ```C
  #include <stdlib.h>
  
  typedef struct {
    int a, b, c;
  } *DataHandle;
  
  int main() {
    // sizeof icindeki *p unevaluated context olmasi nedeniyle gecerlidir
    DataHandle* p = (DataHandle) malloc(sizeof(*p));
  }
  ```
  
* `sizeof` operatorunun operandi tur bilgisi ile kullanildiginda `()` kullanimi zorunludur, ancak bu parantez operatorun bir parcasi degildir.
  ```C++
  int x = 10;
  
  sizeof int;   // sentaks hatasi
  sizeof(int);  // gecerli
  sizeof x;     // gecerli
  ```

## Unary `+`/`-` isaret operatorleri
* Operand `int` alti turlerden ise **integral promotion**a neden olur.
   ```C++
   char c = 'A';
   
   auto x = c;  // x = char
   auto y = +x; // y = int (integral promotion)
   ```
* Operandina bir **lvalue expression** oldugunda ifadeyi **prvalue**'ya cevirir.
   ```C
   int x;
   x;   // ifadenin deger kategorisi lvalue
   +x;  // ifadenin deger kategorisi rvalue
   ```

## Logic `&&` ve `||` operatorleri
<!-- TODO -->

### short circuit behavior
Once sol operand sonra sag operand degerlendirilir. Eger sol operand ile nihai sonuc kesin olarak elde edilmis ise sag operand icin islem kodu yurutulmez.
```C++
int x = 0;
int y = 10;

int z = x && ++y; // x false olmasindan dolayi y icin islem kodu yurutulmeyecektir.
```
```C++
// i < 10 yanlis ise a[i] ifadesi icin islem kodu yurutulmeyecektir.
int a[SIZE];
for(int i = 0; i < 10 && a[i] != val; i++);
```

## Atama operatorleri
* Tum atama operatorlerinin urettigi deger, nesneye atanan degerdir.
  ```C
  x = y;      // uretilen deger x'e atanan deger
  ```
  Atama operatorunun urettigi deger `y` degildir, `x`'e atanan degerdir. Cunku, tur donusumu olmasi durumunda atanan deger donusume ugramis degerdir.
  ```C++
  if((ptr = malloc(sizeof(int))) != NULL) {
    
  }
  
  while((ch = getchar()) != '\n'){
    
  }
  
  while((c = fgetc(f)) != EOF);
  ```

## Prefix `++`/`--` ve Postfix `++`/`--` operatorleri

```C++
int x = 10;
int y;

y = x++;    // x++'nin urettigi deger x'in degeri
y = ++x;    // ++x'nin urettigi deger x'in degerinin bir fazlasi
```

> :warning: 
> Operatorun urettigi deger ile yan etkisi karistirilmamalidir.

## Comma `,` operatoru

```C++
expr1, expr2
```
1. comma operatoru bir sequence point olusturur.  
   expr1 her zaman expr2'den once evaluate edilir ve tum side-effectler gerceklesir.
2. Urettigi deger sag operandin degeridir.  
   Yukaridaki ifade expr2 degerini uretir.

* Operatore olan virgul ile ayrac olan virgul birbiri ile karistirilmamali
  ```C
  void func(int, int, int);
  
  int x = 10, y=20;
  int a[] = { 1, 2, 3};
  func(x, y, 5);  // bu satira kadar hepsi ayrac
  
  int b[] = { 1, (2, 3)}; // 1, ifadesinde ayrac, (2,3) ifadesinde virgul operatoru
  func((x, y, 5));        // hepsi virgul operatoru
  ```

<details>
<summary><b>Ornekler</b> (Click to expand)</summary>

* 
  ```C++
  if(++x, f(x) != 0); // x 1 arttirilir ve f(x) cagrisi sonucu sifir ile karsilastirilir.
                      // Karsilastirma sonucu if deyiminde kullanilir
  ```
* 
  ```C++
  if(a > 10)
    ++x, ++y, ++z;
  
  if(a > 10){
    ++x;
    ++y;
    ++z;
  }
  ```
* 
  ```C++
  int a[5] = {1, 2, 3, 4, 5};
  for(auto x : a)
    cout << x << ' ';   // prints 1 2 3 4 5
    
  int b[5] = {1, (2, 3, 4, 5)};
  for(auto x : b)
    cout << x << ' ';   // prints 1 5 0 0 0 
  ```
* 
  ```C++
  int a[] = { (exp1, 0), (exp2, 0), (exp3, 0) };                  // a = {0, 0, 0};
  std::initializer_list<int> { (exp1, 0), (exp2, 0), (exp3, 0) }; // {0, 0, 0}
  ```

* [Soru](res/sorular/soru23.cpp)
  ```C++
  int x = 10, y = 20;
  int z;
  
  z = x, y;     // z = 10 atama operatoru virgul operatorunden daha onceliklidir.
  z = (x, y);   // z = 20 Parantez, atama operatorunden yuksek onceliklidir.
                //        Virgul operatoru sag operandin degerini uretir.
  ```
</details>
<!--  -->

## sequence point and order of evaluation
*sequencing*  

Sequence point, bulundugu konumdan önceki değerlendirmelerden kaynaklanan tüm yan etkilerin tamamlandığı ve sonraki değerlendirmelerin hiçbir yan etkisinin başlamadığı kaynak kodda bir noktadır. Compile-time'e iliskin bir kavramdir.

* Atama, increment ve decrement operatorlerinin yan etkisi bulunmaktadir, diger operatorlerin yan etkisi yoktur.

* Operator onceligi, islemin daha once yapilmasi anlamina gelmemektedir:
  ```C
  f1() + f2() * 5; 
  ```
  ```C
  x = 10;
  x++
  ```
  Yukaridaki ornekte `x`'in degeri ne zaman 11 olacak?
  ```
  ++x
  ---------- code point/seq point
  burada x'in degeri kullanildiginda yan etkiler uygulanmis ve degeri 11'dir
  ```

* Eger bir nesne yan etkiye maruz kalmis ve ayni ifade icerisinde sequence point'den once kullanilmis ise hem C'de hem de C++'da **UB**dir.
  ```C++
  ++x + x
  ```

> :warning: 
> C ve C++'da sequence point kurallari farklidir. 

**Tipik sequence pointler**
1. Deyim sonu
    ```C
    statement;
    ```
2. Bildirimlerdeki virgul  
    ```C
    int x = 5, y = ++x, z = y + x;
    ```
3. Kontrollerin ifadelerinde kullanilan `()`'den sonra
   ```C++
   if(expr)
   while(expr)
   do while(expr);
   for(;;)
   switch()
   ```
4. `&&` ve `||` sol operandi evaluate edildikten sonra seq pt vardir
   ```C++
   x = 4;
   x++ && f(x); // f fonks. 5 degeri ile cagrilir.
   ```
5. Comma operatorunun sol operandi evaluate edildikten sonra seq pt vardir
   ```C++
   if(++x, f(x) != 0);
   ```
6. `?:` operatorunun `?`da bir sequence pt vardir.
   ```C++
   int x = 4;
   x++ ? foo(x) : foo(x);
   ```

## `<<` ve `>>` bitwise shift operatorleri

* Sag operandin degeri, sol operanding donusturulmus turunun bit sayisindan kucuk ve pozitif bir deger olmasi gerekir. Aksi halde **UB**dir.
  `int`'in 32 bit oldugu varsayilir ise:
  ```C++
  int x = 0;
  x << 33;   // UB
  x << -3;   // UB
  ```
  `int` 32 bit, `short` 16 bit oldugu varsayilir ise:
  ```C++
  int x = 17;
  short s = 98;
  s << x;    // gecerli
             // s degeri integer promotion'a ugradigi icin x degeri 32'den kucuk olmalidir.
  ```
* Negatif degerleri `<<` (sola kaydirma) **UB**dir.
* `signed` ve negatif bir deger `>>` isleminde soldan eklenecek bitlerin degeri **implementation-defined**dir.

## Karsilastirma operatorleri

Karsilastirma operatorlerinde sik yapilan yapilan hatalar:
* Gercek sayilarin `==` karsilastirmasi yapilmasi
  ```C++
  double x = 0.;
  for(int i=0; i<10; ++i)
  x += .1;
  
  auto b = x == 1.0;   // b = false
  ```
* `==` yerine yanlislikla `=` kullanilmasi
  ```C++
  if(a = 5);
  ```
  Bu durumda sentaks hatasi uretilebilemesi icin`lvalue == rvalue`  yerine `rvalue == lvalue` yazilabilir:
  ```C++
  if(5 = a);  // senktaks hatasi
  ```

## `?:` ternary operator
**Kullanildigi tipik senaryolar**  
* Kosula bagli initialization:
  ```C++
  z = x > y ? a : b;
  ```
* Kosula bagli fonksiyon cagrilari
  ```C++
  f(a > b ? a : b);
  ```
* Kosula bagli geri donus degerleri:
  ```C++
  int func() {
    // ...
    return a > b ? a : b;
  }
  ```

# Tur-es isim bildirimleri

> :information_source: 
> Bir tur es ismi tanimi icin:
> 1. Hangi ture es isim verilecekse o turden bir degisken tanimla
> 2. Basina `typedef` koy.
> 3. Degiskenin ismini tur es ismi olarak degisitir.
