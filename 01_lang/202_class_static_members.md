# Static Class Members

## Static Data Members
Static data memberlar, nesneye ait degil, sinifa aittir.

**Bildirim**
```C++
class Myclass {
public:
    static int x;
};
```
**Tanim**
Definition'da `static` anahtar sozcugu kullanilmaz.
```C++
int Myclass::x;       // default init (static oldugu icin zero init olmasi garanti)
int Myclass::x = 0;   // 
int Myclass::x(0);    // direct init
int Myclass::x{}      // value init
int Myclass::x{ 0 };  // direct list init
```

> **DIKKAT**
> Sinifin icinde bildirilen yalnizca bir bildirimdir. Derleyici bu degisken icin henuz yer ayirmiyor. (non-defining declaration)
> *unresolved externals linker error!*

---------

**Static data member vs Global variable**
Farklar:
1. Class scope icindedirler. *(isim arama)*
2. Access control'a tabi olur.

Benzerlikler:
1. [statik omurlu](050_basics.md#static-storage)
2. [Static initialization fiasco](999_kavramlar.md#static-initialization-fiasco)
3. inline olarak tanimlanabilir [C++17]

-------
**Name lookup**

Client kodlarin static data memberlari kullanabilmesi icin 2 sart yerine getirilmis olmasi gerekiyor:
1. Nitelenmis bir isim olmasi
2. Access control'e uygun olarak erisilebilir olmasi
   
   <!--  -->
   
   > **DIKKAT**
   > Static bir veri elemanina ilk deger veren ifade once class scope icinde aranir.

* Sinifin statik data member'larina `.` ve `->` operatorkeri kullanilarak erisilebilmektedir.
  *Bazi programla dillerinde sinifin static member'larina nesne uzerinden erisilmesi sentaks hatasi olabilir, C++'da durum boyle **degildir**.*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  Myclass m1, m2;
  Myclass* p { &m1 };
  Myclass& r = m2;
  
  m1.x = 10;    // legal
  m2->x = 20;   // legal
  m3.x = 30;    // legal
  ```
  </details>
  <!--  -->

----------

* Sinifin tanimi icinde bildirimi yapilan static data memberlar, sadece bir bildirim olduklari nedeniyle, bir **incomplete type**'a iliskin olabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Nec;    // forward declaration
  
  class Myclass {
  private:
    static Nec nec2;    // legal
  };
  ```
  </details>
  <!--  -->
  
* Bir sinifin static data memberi sinifin kendi turunden olabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    Myclass m;          // syntax error: Incomplete type
    static Myclass m;   // legal
  };
  ```
  </details>
  <!--  -->

* Eger static data member `const` bir tamsayi turlerinden biri ise; sinif blogu icinde tanimlanabilirdir. 
  *Bu kural Modern C++'dan oncesinden beri bulunmaktadir.*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    static const int x = 5;     // legal
    static int x = 5;           // illegal: const degil
    static const double x = 5.; // illegal: integral type degil
    static const long x = 5;    // illegal
  };
  ```
  </details>
  <!--  -->
  
* [C++17] Sinifin static data member'lari `inline` anahtar sozcugu ile inline olarak sinif icinde tanimi yapilabilir. [[bknz: Inline variables](160_odr.md#inline-variables-c17), [ODR](160_odr.md#one-definition-rule-odr)]
  ```C++
  class Myclass {
  public:
    inline static int x = 5;                    // legal
    static inline std::string str = "necati";   // legal
  };
  ```

---------------

**Kullanim Ornegi**

* Sinifin genel isleyisi ile ilgili lookup tablolari
  ```C++
  class Date { 
  private:
    inline static constexpr const char* weekdays[] = {"Pazartesi", "Sali"};
    constexpr static int daytabs[] = {31, 28 };
  };
  ```
  > **Not**  
  > Sinifin static data member degisime tabi ise encapsulation uygulanmasi tavsiye edilir.



## Static Member Functions
Sinifin geneli ile ilgili bir is yapan ancak nesne ozelinde is yapmayan fonksiyonlardir.

```C++
class Myclass {
public:
    static void func(); // static member function
};
```
```C++
Myclass::func();
```

* Class scope icinde bulunurlar.
* Fonksiyon taniminda `static` anahtar sozcugu **kullanilmamalidir**.
* Sinifin icinde tanim `inline` olarak yapilabilmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    static void bar() 
    {
    }
  };
  ```
  </details>
  <!--  -->
* Access control'e tabi tutulmaktadirlar.
* Sinifin private ogelerine erisebilirler.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    static void bar();
  private:
    int mx;
  };
  
  void Myclass::bar() 
  {
    Myclass m;
    auto x = m.mx;
  }
  ```
  </details>
  <!--  -->

* Siniflarin static member fonksiyonlari, siniflarin statik veri elemanlarini unqualified isim ile kullanabilirler.

* Static member function bir `this` pointera sahip degildir.
  *Yani bir sinif nesnesinin adresi ile cagrilmamaktadir.*

* Siniflarin static member fonksiyonlari, siniflarin statik data memberlarini unqualified isim ile kullanabilirler.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    static int get_mx(){
        return mx;
    }
  private:
    static int mx;
  };
  ```
  </details>
  <!--  -->
  
  
* Sinifin static member function'lari, sinifin non-static data member'larini **unqualified** olarak kullanamazlar. 
  *Cunku ortada bir `this` pointeri yok, hangi nesnenin degeri oldugu belli degil!*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    static void bar(Myclass p) {
        Myclass m;
        auto x = m.mx;
        auto y = p.mx;
        
        auto z = mx;        // sentaks hatasi
    }
  private:
    int mx;
  };
  ```
  </details>
  <!--  -->
 
* Sinifin static member function'lari, `const` uye fonksiyon olamazlar.  
  *Cunku `this` pointeri yok. [[bknz: const member func](200_classes.md#const-member-functions)]*

* Sinifin non-static `const` uye fonksiyonlari, static data memberlarini degistirebilirler.  
  *`const` anahtar sozcugu `this` pointer'ina aittir. [[bknz: const member func](200_classes.md#const-member-functions)]*
  
* Global fonksiyon pointerlari ile statik uye fonksiyon pointerlari arasinda bir fark yoktur.
  ```C++
  class Myclass {
  public:
    static int func(int);
    int bar(int);
  };
  
  int gf(int);
  ```
  ```C++
  int (*fp)(int) = &gf;
  int (*fp2)(int) = &Myclass::func;
  ```
  non-static uye fonks adresi ayri bir turdur:
  ```C++
  fp = &Myclass::bar;   // sentaks hatasi;
  int (Myclass::*f)(int) = &Myclass::bar; 
  ```

* [Ornek: Object Counter](res/src/class_static_members01.cpp)
* [Ornek: Ninja Sinifi](res/src/class_static_members02.cpp)

[SORU](sorular/soru12.cpp)

<!--  -->

### **Named ctor idiom**
*(Isimlendirilmis kurucu islev idiomu)*

* Bir sinif icin kullanici kodlari dinamik omurlu nesne kullanmaya zorlamak  
  *(otomatik veya static omurlu nesne olusturmayi engelleme)*
  ```C++
  class Myclass {
  public:
    static Myclass* create_object(void) {
        return new Myclass;
    }
  
    void foo();
    void bar();
  private: 
    Myclass();
  };
  ```
  ```C++
  auto p = Myclass::create_object();
  p->foo();
  p->bar();
  ```
  
* Ayni imzaya sahip ctor'larin overload edilememesinden dolayi
  ```C++
  class Complex {
  private: 
      // cartesian
      Complex(double r, double i);
      // polar
      Complex(double angle, double distance, int);  // sondaki int func overloading icin dummy olarak eklendi
  public:
      static Complex create_cartesian(double r, double i) {
          return Complex(r, i);
      }
      static Complex create_polar(double angle, double distance) {
          return Complex(angle, distance, 0);
      }
  };
  ```
  ```C++
  auto c1 = Complex::craete_cartesian(2.3, 5.6);
  auto c2 = Complex::craete_polar(2.3, .6);
  ```
  

### **Mono-state Pattern**
Butun elemanlari static olarak kullanilan objelere denir. Her bir obje farkli olmasina ragmen non-static uyesi olmamasindan dolayi state'leri aynidir.

```C++
class Clock {
public:
    static std::time_t now();
    static void adjust();
    static int get_minute();
}
```
```C++
Clock c1;
Clock c2;
Clock c3;
```

### **Singleton Pattern**
Bir sinif turunden tek bir nesne olacak bicimde nesneye global erisim saglamak amaciyla kullanilan bir **creational pattern**'idir.  

> Singleton pattern, GOF Design Patterns kitabinda bahsedilen creational pattern'lerden biridir.  
> 
> Gang of Four: *(Gamma, Helm, Johnson, Vlissides)*

Genel tasarim kriterleri:

* Nesnenin destroy edilmesi gerekiyor mu?
* thread-safe olmasi gerekiyor mu?
* Kalitim olacak mi?
* Lazy initialization gerekiyor mu?

```C++
class Myclass {
public:
    static Myclass* instance() {
        if(!mp_instance)
            mp_instance = new Myclass;
        return mp_instance;
    }
    
    void foo();
    void bar();
    void baz();
private:
    Myclass(); 
    
    // copy members must be deleted
    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;
    
    inline static Myclass* mp_instance{};
};
```
```C++
Myclass* p = Myclass::instance();
p->foo();
p->bar();
Myclass::instance()->baz();
```

**Meyers' singleton**

* Ilk cagri yapildiginda nesne hayata gelecek, sonraki cagrilarda ayni nesne llanilacaktir.
* Ayrica static nesnelerin initialization'i thread-safe'dir.
* Program sonlandirilirken dtor cagrilacaktir.
* copy ctors must be deleted
```C++
class Myclass{
public:
    Myclass(const Myclass&) = delete;
    
    static Myclass& instance() {
        static Myclass m;   
        return m;
    }
    
    void foo();
    void bar();
    void baz();
private:
    Myclass(); 
    
    Myclass(const Myclass&) = delete;
    Myclass& operator=(const Myclass&) = delete;
    ~Myclass();
};
```
```C++
Myclass& r = Myclass::instance();
r.foo();
r.bar();
Myclass::instance().baz();
```