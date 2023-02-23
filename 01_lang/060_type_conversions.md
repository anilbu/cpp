# Type Conversion

Derleyicinin bir islemi yapabilmesi icin bir ifadenin dilin kurallarina gore static olarak kendi turunu kullanmak yerine baska bir turde ifade ederek -cogunlukla bir gecici nesne olusturarak- isleme sokmasidir.

* Implicit Type Conversion
* Explicit Type Conversion

**Narrowing conversation**
Veri kaybina neden olan donusumlerdir.
```C++
double dval = 5.6;
int i1 = dval; 
int i2(dval);
int i3{ dval }; //syntax hatasi, daraltici donusum olmasi nedeniyle
```

## Implicit Type Conversion
Farklı türde bir değerin beklendiği bağlamda bir ifade kullanıldığında, derleyiciye acik olarak bir talimat verilmemesine ragmen *-ortulu olarak-* dilin kurallarina gore tur donusumu yapilabilir.


### 1. Usual Arithmetic Conversion

* Tur donusumu, minimal veri kaybi nedeniyle **ranki daha buyuk olan ture** yapilir.  
* Isaretli ve isaretsiz turlerin rankleri aynidir.
  
```C++
long double > double > float
long long > long > int
```

> **DIKKAT!**  
> `int` alti turler (short, char, bool) **integer promotion**a ugrayarak `int`e cevrildikten sonra islem yapilir.  
> 
> **Ornek**  
> ```C
> short s1 = 5, s2 = 7;
> s1 + s2 // int (integral promotion) 
> ```
> 
> ```C++
> char c = 'A';
> c   // char
> +c  // int (char'dan int'e integral promotion)
> ```

<!--  -->

**Kurallar**
1. Eger **farkli rankler** ve **isaretler ayni** ise islem **yuksek rank**'te yapilir.
2. Eger **farkli rankler** ve **farkli isaretler** ise islem her zaman **rank'i yuksek olan isaretsiz turde** yapilir.
   ```C++
   unsigned long + int => unsigned long
   ```
3. Eger **rankler farkli** ve **dusuk rank isaretsiz** ise,
   1. Eger yuksek rank dusuk olan rankin tum degerlerini **barindirabiliyor** ise islem **yuksek rank**te yapilir.
      ```C++
      long + unsigned int => long
      ```
   2. Aksi halde islem **yuksek olan rankin isaretsiz** turunde yapilir.
      ```C++
      long + unsigned int => unsigned long
      ```
4. Eger **rankler ayni** ve **isaretler farkli** ise, islem her zaman **isaretsiz** turde yapilir.
   ```C++
   unsigned + int => unsigned
   ```

<!--  -->

* `signed int` turu `unsigned int` turune donustururken bitler degistirilmez!
  ```C++
  int x = -1;
  unsigned int y = 1;
  
  auto b = x > y;
  ```
  `b` false olur, cunku `x` degeri once unsigned ture donusturulur ve bitleri degistirilmedigi icin `y`'den buyuk bir sayi olur!
  [Soru](sorular/soru1.cpp)
* **Isaretli turlerde** bir aritmetik **tasma** olusmasi **UB**'dir.
* Isaretsiz turlerde tasma soz konusu degildir, moduler aritmetik gibi basa doner.
* Gercek sayi turunden tam sayi turune donusumde once ondalik kisim kaybedilir. Kalan sayi tam sayi turune **sigmiyorsa** **UB**'dir.
* Bir nesnenin compile-time'da belirlenmis turu hicbir zaman degistirilemez.
* Tur donusum operatoru ile olusturulan ifade bir **rvalue expression**dir.
  ```C++
  (int)dval = 10;   // sentaks hatasi
  ```
<!--  -->

### 2. Assignment/Copy Conversion
Asagidaki durumlarda turler farkli ise derleyici bir tur donusumu gerceklestirmektedir.

1. Bir degiskene ilk deger vermek
2. Bir degiskene atama yapmak
3. Bir fonksiyona arguman gondermek
4. Return ifadeleri

<!--  -->

### Derleyici hangi durumlarda implicit donusum yapmak zorundadir?
Eger bir ortulu donusum (implicit conversion); 
 1. `standard conversion + user-defined conversion` olarak
 2. `user-defined conversion + standard conversion` olarak
 
gerceklestirilebiliyor ise, derleyici bu donusumu yapmak zorundadir. 

Ancak, derleyici `user-defined conversion + user-defined conversion` donusumu mumkun olsa dahi bu donusumu ortulu olarak yapmayacaktir.

  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  * ```C++
    class Myclass {
    public:
        Myclass();
        Myclass(int);
    };
    ```
    ```C++ 
    Myclass m;
    double dval{};
    m = dval;     // gecerli: double->int->Myclass donusumu gecerlidir,
                  //    cunku double->int std conv, int->Myclass user-def conv
                  //    static_cast<Myclass>(static_cast<int>(dval))
    
    m = 10 > 5;   // gecerli: Cunku bool->int->Myclass donusumu gecerlidir.
    ```
  * ```C++
    class Myclass {
    public:
        Myclass();
        Myclass(bool);
    };
    ```
    ```C++
    int x;
    int* ptr = &x;
    Myclass m;
    m = ptr;    // gecerli: int* -> bool -> Myclass 
              // std.conv. + user-def conv olmasindan dolayi derleyici donusumu yapmak zorunda!
    ```
  * ```C++
    struct B {
      B(A);   // A'dan B'ye ortulu donusum
    };
    
    struct C {
      C(B);   // B'den C'ye ortulu donusum
    };
    ```
    ```C++
    A ax;
    C cx = ax;    // sentaks hatasi: implicit user-def + user-def conv.
    ```
  </details>


## Explicit Type Conversion
Derleyiciye donusum yapma talimatinin **acik olarak** belirtildigi tur donusumudur.

C dilinde type convversion ile tur donusumunun niyeti dilin araclari ile acikca belirtilemiyor:
```C++
(target_type) expr;
```
**Explicit tur donusumu gerektiren durumlardan bazilari**  
* Iki tamsayi bolumunden bir gercek sayi elde edilmek istenmesi
  ```C++
  (double)i1 / i2;
  ```
* Isaretli turlerde overflow (UB) riski olan durumlarda
  ```C++
  (long long)i1 * i2;
  ```
* Narrowing conversion soz konusu oldugunda kodun amacini daha acik belirtme
  ```C++
  ival = (int)dval; // veri kaybi bilincli olarak yapildiginin belirtilmesi
  ```
* Nesnenin kendisi const degil ancak sozleme bagli (contractual constness) bir const durumu bulunuyor.
  ```C++
  int x = 10;
  const int* ptr = &x;
  
  *ptr = 45;           // sentaks hatasi, cunku ptr const int'e isaret eder
  int* p = ptr;        // sentaks hatasi, cunku const T*'dan T*'a implicit donusum yok
  int* p = (int*) ptr; // legal, logic olarak x const degil ve niyet belirtilmis
  *p = 56;             // legal
  ```
* Bir nesneyi baska turden bir nesne gibi kullanilmak istenildiginde [[bknz: type punning](999_kavramlar.md#type-punning)]
  ```C++
  float pi = 3.14159;
  uint32_t piAsRawData = *(uint32_t*)&pi;
  ```
  > **DIKKAT!**  
  > Adres donusumlerinden bazilari legal, bazilari **UB** olabilir!  
  > Tur donusumunden mumkun oldugunca kacinilmalidir. Bazi durumlarda explicit tur donusumu   uygulanmis olsa dahi **UB**a neden olabilir.
  > ```C++
  > int ival = 10;
  > double dval = 3.14;
  > 
  > double* dptr = (double*) &ival; // legal, ancak dogru degil
  > *dptr;                          // UB!
  > ```

Modern C++'da farkli niyetlerle yapilan donusumler icin farkli operatorler bulunmaktadir.
* `static_cast`
* `const_cast`
* `reinterpret_cast`
* `dynamic_cast`

<!--  -->

Parantezler `()` type cast operatorlerin sentaksina **dahildir**.
  
> **Not**  
> Eski tur donusum operatorunu mumkun oldugunca kullanilmasi tavsiye edilmiyor. Yerine C++'in modern tur donusum operatorlerinin kullanilmasi tavsiye edilmektedir.
> 
> Yeni tip tur donusumlerinin kullaniminun bir avantaji da tur donusumlerinin kod icinde kolaylikla tespit edilebilir olmasidir.

### `static_cast` operatoru
Gercek sayi turleri, tamsayi turleri ve enum turleri arasindaki donusumleri yapar.
```C++
static_cast<target_type>(operand)
```

* `static_cast` ile `const` dusurulemez.

**Ornekler**
```C++
double dval = static_cast<double>(ival1) / ival2;
int ival = static_cast<int>(dval);
```
```C++    
enum class Pos{off, on, hold};
Pos mpos = Pos::off;
ival = mpos;    // sentaks hatasi: scoped-enum'dan aritmetik turlere impl. cast yok
ival = static_cast<int>(mpos);  // legal
```


### `const_cast` operatoru
`const T*`'dan `T*`'a yada `T*`'dan `const T*`'a yapilan donusumleri gerceklestirir.
```C++
const_cast<target_type>(operand)
```
**Ornek**
Verilen bir cstring uzerinde aranilan karakterin adresini, bulunamazsa `nullptr` dondurecek accessor bir fonksiyon:
```C++
char* mystrchr(const char* p, int c)
{
    while(*p) {
        if(*p == c){
            return const_cast<char*>(p);
        }
        ++p;
    }
    
    if(c == '\0')
        return const_cast<char*>(p);
    
    return nullptr;
}

mystrchr("abc", 0);
```
> **Not**  
> p parametresinin `const char*` olmasinin nedeni adresi verilen nesnenin degistirilmeyecek olmasidir. 
> Geri donus degerinin `char*` turu olmasinin nedeni `p` parametresine verilen argumanin `const` olup olmadiginin bilinmemesidir. 


### `reinterpret_cast` operatoru
Bir turden nesneyi baska turden bir nesne olarak kullanilmasi amaciyla kullanilir.
```C++
reinterpret_cast<target_type>(operand)
```

**Ornekler**
Bir `double` degerinin `byte`larina erisim:
```C++
double dval = 456.7890;
char* p = reinterpret_cast<char*>(&dval);

for (size_t i{}; i < sizeof(double); i++)
{
    cout << static_cast<unsigned int>(p[i]) << endl;
}
```
`const T*`'dan `T*`'a donusum yok, birden fazla donusum yapilmasi gerekmektedir. 
```C++
const unsigned int uval{436u};
int* p1 = const_cast<int*>(reinterpret_cast<const int*>(&uval));    // legal option 1
int* p2 = reinterpret_cast<int*>(const_cast<unsigned int*>(&uval)); // legal option 2
```

### `dynamic_cast` operatoru
Runtime polymorphism amaciyla kullanilir. `Base` siniftan `Derived` sinifa yada `derived` siniftan `base` sinifa yapilan donusumleri gerceklestirir.
```C++
dynamic_cast<target_type>(operand)
```
[bknz: Dynamic cast operatoru](./330_rtti.md#dynamic_cast-operatoru)  
