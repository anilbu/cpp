# Constructors and Destructor

**Constructor**
[cppreference.com - constructor](https://en.cppreference.com/w/cpp/language/constructor)
Constructor, sınıf türündeki nesneleri initialize etmek için kullanılan bir sınıfın statik olmayan özel bir üye işlevidir.
```C++
class Myclass {
public:
    Myclass();
};
```
```C++
Myclass::Myclass() { }
```

* Ctor ismi sinifin ismi ile ayni olmak zorundadir.
* Ctor geri donus degeri **kavrami** yoktur.
  *`void` turu kavramsal olarak bos bir geri donusu ifade etmektedir.*
* Sinifin **non-static** uye fonksiyonu olmak zorundadir. Global, static yada const uye fonksiyon olamaz.
  *`this` pointeri kullanilabilir.*
* Ctor **overload edilebilir**.
* `public` uye fonksiyon olmak zorunda degildir.
* Ctor `.` yada `->` operatorleri ile ismi ile dogrudan cagrilamaz.

**Destructor**
Destructor, bir nesnenin hayati sona erdiğinde çağrılan özel bir üye işlevdir. Amacı, nesnenin ömrü boyunca edinmiş olabileceği kaynakları serbest bırakmaktır.

```C++
class Myclass {
public:
    ~Myclass();
};
```
```C++
Myclass::~Myclass() { }
```

* Dtor'un ismi class ismi ile ayni olmak zorunda ancak basinda `~` olmalidir. 
* Dtor geri donus degeri **kavrami** yoktur. 
  *`void` turu kavramsal olarak bos bir geri donusu ifade etmektedir.*
* Sinifin **non-static** uye fonksiyonu olmak zorundadir. Global, static yada const uye fonksiyon olamaz.
  *`this` pointeri kullanilabilir.*
* Dtor'in parametre degiskeni olamaz. Dolayisiyla dtor **overload edilemez**.
* `public` uye fonksiyon olmak zorunda degildir.
* Dtor `.` yada `->` ile ismi ile dogrudan -bazi ozel durumlarda kullanilmak uzere- cagrilabilir. [[bknz: `placement new`](res/src/placement_new01.cpp)]
  
**Bir ctor/dtor fiilen ne zaman cagrilmaktadir?**

<!--  -->

* **global sinif nesneleri**
  * ctor, main fonksiyon cagrilmasindan once cagrilir.
  * Birden fazla global nesne olmasi durumunda bildirim sirasi ile olusturulur. [[bknz: static initialization fiasco](999_kavramlar.md#static-initialization-fiasco)]
  * dtor, main fonksiyon kodunun calismasindan sonra cagrilir.
  * Hayata ilk gelen, ilk sonlanir. 
    *dtor'lar ters sira ile cagrilacaktir.*

<!--  -->

* **static yerel sinif nesneleri**
  * Hayata gelmeleri icin tanimladiklari fonksiyonun en az bir kere cagrilmasi gerekmektedir.
  * Fonksiyon tekrar cagrildiginda nesne tekrar olusturulmaz, ilk olusturulan kullanilir.
  * dtor, main fonksiyon kodunun calismasindan sonra cagrilir.

<!--  -->

* **otomatik omurlu sinif nesneleri**
  * Programin akisi o koda her geldiginde hayata gelecektir.
  * Olusturulduklari scope sona erdiginde dtor cagrilir.

<!--  -->

* **dinamik omurlu sinif nesneleri**
  * Programin calismasindan veya scopelardan bagimsiz olarak; diledimiz zaman hayata getirip diledigimiz zaman hayatlarini sonlandirabildigimiz nesnelerdir.
    
<!--  -->

[Ornek: Ctor ve Dtor cagrilarinin yapilmasi sirasi](res/src/class_ctor01.cpp)

> **DIKKAT!**  
> Dynamic storage ile dynamic storage duration birbiri ile karistirilmamalidir. [[bknz: storage classes](063_storage_classes.md)]
>
> Dinamik omurlu nesne ayri bir kavram, programin calisma zamaninda dinamik olarak bellek alani elde etmek birbiri ile iliskili ancak farkli kavramlardir. [[bknz: new/deleteoperator ](900_dynamic_memory.md)]

## Default constructor
*Argumant gonderilmeden cagrilabilen ctor*
Parametre degiskeni olmayan yada tum parametre degiskenleri varsayilan argumani olan ctordur.

**Hangi durumlarda default ctor cagrilir?**
1. Default initialization  
   ```C++
   Nec n1;
   ```
   Primitive tipler icin garbage deger ile init edilirken, sinif nesneleri icin default ctor ile init edilir.

   > **DIKKAT!**
   > Alttaki ifade bir function declaration, degisken definition degil. [[bknz: most vexing parse](999_kavramlar.md#most-vexing-parse)]
   > ```C++
   > Nec x();
   > ```

<!--  -->

2. Value initialization  
   ```C++
   Nec n2{};
   ```
   * Primitive tipler icin zero ile init edilirken, sinif nesneleri icin default ctor ile init edilir.
   * Default ctor'dan once elemanlar zero init edilir.

<!--  -->

3. Sinif turunden arrayler
   ```C++
   Nec n3[10];
   ```
   Dizinin elemanlarinin bir sinif turunden olmasi durumunda:
   * Dizinin her bir elemani icin default ctor cagrilir.
   * Elemanlarin ctorlari dizinin basindan sonuna dogru sirayla cagrilir. dtor ise ters sira ile cagrilir.


> **DIKKAT!**  
> Bir sinifin default ctor'u olmak zorunda degildir.
>
> Parametreli bir ctor bildirildiginde default ctor **not declared** olur. Eger default ctor gerektiren bir durumda ctor'un var olmamasi durumunda syntax hatasi olusur. 


## Constructor Initializer List
*member initializer list*

Hayata getirilen sinif nesnesinin **non-static data member**'larini initialize etmek icin kullanilan bir aractir.
```C++
class Myclass { 
public:
    Myclass() : mx(10), my(20), md(3.14) 
    {
        // statement
    }

private:
    int mx, my;
    double md;
};
```
* Yanlizca ctor'lar icin kullanilabilir.
* Initializer list, ctor ana blogundan once calistirilir.
  *Eger programin akisi ctor ana blogu icindeki kodlari yurutmekteyse, sinifin tum veri elemanlari hayata gelmis demektir.*
* Ctor init list'de `{ }` ile de initialization yapilabilir.[C++11]
  > **Hatirlatma**
  > `{ }` ile narrowing conversion yapilmasi syntax hatasi olusturur.
* Initialize edilmeyen data memberlar, default initialize edilir.
  *Bu durumda primitive data member'lar, garbage value ile initialize edilir.*

<!--  -->

* Ctor body'sinde initialization degil, assignment yapilir.  
  Asagidaki durumda data members once garbage deger ile init edilir, daha sonra assign edilir.
  ```C++
  class Myclass { 
  public:
      Myclass()
      {
          mx = 10;      // assignment
          my = 30;      // assignment
          md = 4.5;     // assignment
      }

  private:
      int mx, my;
      double md;
  };
  ```
  Yukaridaki kullanim icin duruma gore:
  * Syntax error olabilir. 
    *Referans yada `const` turden degerler default initialize edilemezler.*
  * Efficiency problemi olabilir
  * Ciddiye alinacak bir fark da olmayabilir
  
  > **Not**
  > **ctor initializer list** kullanimi oncelikli olarak diger yontemlere tercih edilmelidir.
  
* Sinifin data memberlarin hayata gelme sirasi **bildirimdeki siralari**dir.
  ```C++
  class Myclass {
  public:
       Myclass() : m_b(10), m_a(m_b * 20) {}
  private:
       int m_a, m_b;
  };
  ```
  Bildirim sirasindan dolayi once `m_a` daha sonra `m_b` initialize edilir. Bu nedenle `m_a` degeri `m_b * 20` yerine garbage deger ile init edilir. Bu durumda **UB** olusur.
  > **DIKKAT!**
  > ctor initializer list'de de bildirim sirasi ile yazilmasi yukarida ki durumun daha kolay farkedilmesini saglar.

* Ctor initializer list, ctor'un taniminda kullanilir.
  date.h:
  ```C++
  class Date{ 
  public:
      Date(int, int, int);
      
  private:
      int m_day, m_mon, m_year;
  };
  ```
  date.cpp:
  ```C++
  Date::Date(int day, int mon, int year) : m_day{day}, m_mon{mon}, m_year{year}
  {
  }
  ```
  
## Default Member Initializer
*in-class initializer*

Default member initializer, ctor initializer list'de initialize edilmez ise varsayilan bir deger vermek icin bir aractir. Member'i fiilen initialize etmez.

**Ornek**
Asagidaki kodda `mx` degeri initialize edilmezse `10` degeri ile default initialize et anlamina gelmektedir. Eger baska bir deger ile initialize edilirse, bu deger kullanilmaz.

Asagidaki ornekte `mx` data member initialize edilmedigi icin default initialize edilirken dmi'de verilen varsayilan `10` degerini kullanilir. `mz` data memberi `90` degeri ile init edilir, dmi'de verilen varsayilan deger `20`'e bakilmaz.
```C++
class Myclass {
  Myclass() : my{ 20 }, mz{ 90 } {}
private:
  int my;
  int mz{ 20 };       // default member initializer
  int mx{ 10 };       // default member initializer
  double dval = 3.14; // default member initializer
};
```
> **DIKKAT!**  
> Default member initializer, `=` ile kullanilabilir ancak normal parantez `( )` ile kullanilamamaktadir. 

> **Not**
> Eger;
> 
> * Compile-time'da member'larin alacagi degerler biliniyor ise
> * Birden fazla ctor overloadu olmasi durumunda, kod tekrarindan kacinilmak isteniyorsa
> 
> in-class initializer kullanimi kolaylik saglamaktadir.

## Parametreli Constructor
```C++
class Myclass {
public:
    Myclass(int x){
        std::cout << "Myclass(int x) x = " << x << '\n';
    }
    
    Myclass(int x, int y){
        std::cout << "Myclass(int x, int y) x = " << x << "y = " << y << '\n';
    }
};
```
```C++
Myclass x1(10);         // direct initialization
Myclass x2{20};         // direct list initialization / brace init
Myclass x3 = 30;        // copy initialization

Myclass x4(4, 5);       // direct initialization
Myclass x5{6, 7};       // direct list initialization / brace init
Myclass x6 = { 9, 12};  // copy initialization
```

> **HATIRLATMA**  
> Brace init `{ }` ile narrowing conversion olusur ise syntax hatasi olusur.


## Conversion Constructor
Aslen varlik nedeninin yani sira, ortulu tur donusumlerini tanimlamak amaciyla kullanilabilen `ctor`lardir. SMF'lerden biri degildir.

Sinif turunden olmayan bir ifade, sinifin **conversion ctor**lari kullanilarak sinif turune donusturulebilirler.
```C++
class Myclass {
public:
    Myclass() = default;
    Myclass(int);   // sinifin int turu conversion ctor'u
};
```
`12` degeri `Myclass` turune [gecici nesne](230_temp_objects.md) olusturularak implicit olarak donusur ve atama yapilir:
```C++
Myclass m;
m = 12; // m = Myclass{12};
```
[Ornek](res/src/ctor_conversion01.cpp)

> **DIKKAT!**
> Conversion ctor'un yanlislikla kullanilmasi durumunda derleyici implicit olarak donusumu gerceklestirebilmesi nedeniyle hata uretmeyecegi icin tespiti zor kodlama hatalarina neden olabilmektedir.

**Neden ortulu donusumler tehlikeli?**
* Implicit olarak conversion ctor ile donusum tehlikeli durumlar ortaya cikarmaya musaittir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Array {
  public:
    Array();
    Array(std::size_t size);    // size adet elemanli array olustursun
  };
  
  void func(const Array&);
  ```
  ```C++
  int x = 40'000;
  func(x);  // (muhtemelen yanlislikla) 40k elemanli array olusturuldu
  ```
  </details>
  <!--  -->
  
* Bir sinifa primitive tipten bir conversion ctor olusturulmasi ile sadece o ture donusum degil, o ture standard donusum ile donusebilen tum turler icin ortulu donusumun olabilmesini saglanir. [[bknz: Implicit conversions](060_type_conversions.md#derleyici-hangi-durumlarda-implicit-donusum-yapmak-zorundadir)]


### `explicit` keyword
Bir ctor icin, user-defined conversion'larin ortulu tur donusumleri yapmamasini saglayarak, sadece explicit donusumlere izin vermek icin kullanilir.

```C++
class Myclass {
public:
    Myclass();
    explicit Myclass(int);
};

Myclass::Myclass(int x) {}
```
```C++
Myclass m;
m = 5;                          // syntax error: cunku explicit
m = static_cast<Myclass>(5);    // gecerli
```

* `explicit` anahtar sozcugu sadece bildirime yazilir, tanimda yazilmaz.
* `explicit` ctor'lar, function overload resolution'da viable fonksiyonlardan cikarilir.
  [Ornek](res/src/ctor_conversion03.cpp)
* Default ctor veya birden fazla parametreli ctor'larada da `explicit` keywordu kullanilabilir, ancak pratikte cok fayda saglamayabilir.

> **Not**
> Oneri olarak; tek arguman ile cagrilabilen bir ctor olustururken default olarak explicit olusturun, eger gerekli goruyorsaniz implicit olarak birakin.



## Delegating a Constructor [C++11]
Bir sinifin birden fazla ctor'u ortak bir kod kullanma ihtiyaci oldugunda; sinifin ctor'u nesneyi hayata getirme islevini baska bir ctor'a delege edebilmesi icin Modern C++ ile eklenmis bir aractir.

```C++
class Myclass
{
public:
    Myclass(const char *p) : Myclass(std::atoi(p)) 
    {
    }

    Myclass(int x) : Myclass(x,0,0)
    {
    }
    
    Myclass(int x, int y, int z) : mx(x), my(y), mz(z)
    {
    }
private:
    int mx, my, mz;
};
```

Modern C++'dan once; farkli yontemler ile yapilabiliyordu.
<details>
<summary><b>Ornek</b> Click to expand</summary>

```C++
class Myclass
{
public:
    Myclass(const char *p)
    {
      init(Myclass(std::atoi(p), 0, 0));
    }

    Myclass(int x)
    {
      init(x,0,0);
    }
    
    Myclass(int x, int y, int z)
    {
      init(x, y, z) 
    }

private:
    void init(int x, int y, int z);
};
```
</details>
<!--  -->


**Problemler**
* ctor cagirisinda initialize edilen data memberlar, `init` fonksiyonunda tekrardan ataniyor.
* `init` fonksiyonunun ismi init olmasina ragmen, aslinda data memberlari initialize etmeyen bir fonksiyondur.
* private uye fonksiyonu client'lar cagiramaz ancak diger private fonksiyonlar yada friend'ler cagirabilir.