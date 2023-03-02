# Non-static Class Members

## Non-static data members
* non-static veri elemanalarini bir incomplete type olamazlar.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Nec;    // forward declaration
  
  class Myclass {
  private:
    Nec nec;            // sentaks hatasi
  };
  ```
  </details>
  <!--  -->

* Bir sinifin non-static data member'i kendi turunden olamaz.
  ```C++
  class Myclass {
  public:
    Myclass m;          // syntax error: Incomplete type
  };
  ```

## Non-static member function
```C++
class Myclass {
public:
  void func(int);
};
```
```C++
void Myclass::func(int)
{
}
```

* Class scope'da tanimlanmis olmalari gerekmektedir.
* non-static member functions bildirildikleri sinifin adresi turunden gizli bir parametreye sahiptir. Bu parametre hangi obje uzerinde islem yapildigini belirtir. [bknz: this anahtar sozcugu](#this-keyword)
* Bir member function, class definition icerisinde tanimlanmis ise default olarak `inline` fonksiyodur. Bu nedenle ODR'u ihlal etmez.
  *Ancak class definition icinde sadece bildirim yapilmis ise bu fonksiyon implicitly inline degildir!*

**Name-lookup kurallari**

Eger bir isim (identifier), sinifin uye fonksiyonu icinde nitelenmeden kullanilmissa
su sira ile aranir:
  1. kullanildigi blok icinde
  2. kapsayan blok icinde (enclosing block)
  3. kapsayan blok icinde (enclosing block)
  4. ...
  5. class scope icinde (class definition)
  6. namespace icinde

Eger isim nitelenmis ise nitelendigi sinif turunun class scope'unda aranir.


> :pushpin: 
> Isim arama bir kez yapilir. Aranan isim bulundugunda isim arama devam etmez. 

> :triangular_flag_on_post: 
> Member func parametreleri de block scope icerisindedir.

**Ornek**
```C++
class Myclass {
public:
    void foo();
private:
    int x;
};

int x = 3478;
```
```C++
void Myclass::foo() {
    int x = 10;
    x = 56;             // isim maskelendi, lokal x
    Myclass::x = 45;    // class scope x
    ::x = 99;           // global x
    
    ::x = x + Myclass::x;   // global x = local x + class x
}
```

> :warning:   
> Class scope'daki bir isim global scope'u maskeliyor olabilir!
> [Soru](sorular/soru10.cpp)

* Sinifin member fonksiyonlari class definition icerisinde tekrardan bildirilemez!
  ```C++
  void foo(int);
  void foo(int);  // function overloading degil, redeclaration
  
  class Myclass { 
  public: 
      void foo(int);
      void foo(int);  // func overloading degil, redeclaration da degil!
  };
  ```
  
* Sinifin member fonksiyonlari overload edilebilir. Access control, function overload resolution'dan sonra yapilir.
  ```C++
  class Myclass { 
  public: 
      void func(int);
      void func(int, int);       // func overloading
  private:
      void func(double);         // func overloading, cunku private ayri bir scope degil
  };
  ```
  ```C++
  Myclass m;
  m.func(3.14); // Access control hatasi: Cunku access control en son yapilir!
                // double overload is not accessible!
  ```
  
### **`this` keyword**
`this` cagrida kullanilan objenin kendi adresini ifade eden bir sinif turunden **pointer**'dir.

* Bu anahtar sozcuk yalnizca sinifin non-static uye fonksiyonlari icerisinde kullanilabilir.
* `this` ifadesinin value kategorisi `prvalue`dur. `*this` ifadesinin value kategorisi `lvalue`dur.
  ```C++
  class Myclass { 
  public:
    void foo() 
    {
        std::cout << "this = " << this << '\n';
    }
  };
  ```
  ```C++
  Myclass m;
  std::cout << "&m = " << &m << '\n';
  m.foo();
  ```
  [Ornek](res/src/class_this01.cpp)

> :triangular_flag_on_post: 
> Member select (`.`) operaturu, dereferencing (`*`) operatorunden onceliklidir.

> :warning: 
> C++'da bir sinifin public interface'i denildiginde:
> * sinifin public uyeleri
> * sinif ile ilgili baslik dosyasinda sunulan global fonksiyonlar (non-member functions)
> 
> Ornek: 
> `operator== `fonksiyonu global olmasina ragmen `std::string` sinifinin public interface'ine **dahildir**.
> ```C++
> std::string s1{ "murat" };
> std::string s2{ "selami" };
> 
> if(s1 == s2) { // operator==(s1, s2)
>  
> }
> ```

[Fluent API (Chaining) in C++](extras/fluent_api.md)


### **`const` member functions**
```C++
class Myclass {
public:
  void set();       // non-const member function
  int get() const;  // const member function
};
```
* const uye fonksiyonlarin `this` pointerinin turu `const T*`'dir.
* const uye fonksiyonlar, sinifin non-static data memberlarini degistiremezler, sinifin non-const uye fonksiyonlarina cagri yapamazlar.
  > :pushpin: 
  > C++'da `const T*` turunden `T*` turune implicit donusumu bulunmamaktadir. [[bknz: implicit type conversions](060_type_conversions.md#implicit-type-conversion)]
* const bir sinif nesnesi, sinifin const uye fonksiyonlarina cagri yapilabilir.
* `const` fonksiyon imzasinin bir parcasidir. Alttaki bildirimler function overloadingdir.
  ```C++
  class Myclass{ 
    void foo();         // (1) func(Myclass*)
    void foo() const;   // (2) func(const Myclass*) const
  };
  ```
  `const` ifadesi fonksiyon imzasinin bir parcasi olmasindan dolayi fonksiyon taniminda da olmak zorundadir.
  ```C++
  void Myclass::foo() const {
    
  }
  ```
  > :pushpin: 
  > `const T*` ve `T*` overloading olusturur. [[bknz: function overloading](140_function_overloading.md#function-overloading-kurallari)] 

**Ornek**
```C++
class Myclass {
public:
    void foo() {
    }
    
    void func() const { 
        mx = 10;    // illegal: const uye func siniflarin non-static data memb degistiremez.
        foo();      // illegal: const uye func siniflarin sadece const uye fonks. cagirabilir.
    }
    
    Myclass* self() const {
        return this;   // illegal: const Myclass* ==> Myclass*'a donusum yok.
    }
    
    const Myclass& self_ref() const {
        return *this;   // gecerli const T ==> const T&'e baglanabilir.
    }
    
    void f() const {
        Myclass m;
        m.mx = 10;  // gecerli: this pointer'i const, m const degil!
        
        Myclass* p = this;  // illegal: const T* ==> T* donusumu yok
    }

private:
    int mx;
};
```
```C++
Myclass m;
m.foo();    // gecerli Myclass* ==> Myclass*
m.func();   // gecerli Myclass* ==> const Myclass*

const Myclass cm;
cm.foo();   // gecersiz: const Myclass* ==> Myclass*'a impl. donusum yok.
cm.func();  // gecerli: const Myclass* ==> const Myclass*
```

[Vector sinifi front fonksiyonu const overloading ornegi](res/src/class_const_memfunc_vector01.cpp)

**`const` olmasi gereken bir uye fonksiyonu non-const yapilir ise neler olur?**
* Kodu okuyani/kullanani nesnenin durumunu degistirdigine dair yaniltabilir.
* Client kodlarin `const` nesneleri ile uye fonksiyona normalde cagri yapabilmesine ragmen cagri yapamayacaklar.
* Nesnenin durumunu degistirmemesi gereken bir fonksiyon icinde yanlislikla state degistirilmesi durumunda hata olusmayacaktir.



### **`mutable` keyword**
Cagri yapan nesne `const` olarak bildirilse bile `mutable` olarak bildirilen sınıf veri üyesinin değiştirilmesine izin verir. Mutable, üyenin sınıfın **harici olarak görünür durumunu etkilemediğini** belirtmek için kullanılır (mutex, memo caches, lazy evaluation ve erişim araçları gibi). [cppreference.com - mutable](https://en.cppreference.com/w/cpp/language/cv)

> **Visible state of an object**  
> Sinifin davranisini degistiren durumu ifade eden degerlerdir.

May appear in the declaration of a **non-static** class members of **non-reference** **non-const** type:
```C++
class Myclass
{
    mutable const int* p; // OK
    mutable int* const q; // ill-formed
    mutable int&       r; // ill-formed
};
```
Asagida ki `get()` fonksiyon nesnenin degerini (value) degistiremez. Nesnenin degeri demek yerine "durumu" (state) demek daha dogru bir tabir olur.

```C++
class Nec {
public:
    void set(int);
    int  get() const;
};
```

* Nesnenin veri elemanlari degismiyor ancak degeri (obsv. state) degisiyor.
  ```C++
  class String {
  public:
      char *mp;   // mp[], pointer adresi degismemesine ragmen degeri degisebilir.
  };
  ```

* Nesnenin veri elemanlari degisiyor ancak degeri (obsv. state) degismiyor.
  ```C++
  class Date {
  private:
      int md, mm, my;
      mutable int m_debug_count;  // Sinifin logic olarak state'i ile ilgili degil.
  public:
      void print() const {
          //...
          ++m_debug_count; // mutable olarak tanimlandigi icin const icinde degistirilebilir
      }
  };
  ```

> :warning: 
> Sinifin tum veri elemanlari (non-static data members) sinif nesnesinin observable state'i ile dogrudan iliskili olmayabilir.

> :warning: 
> Lambda ifadelerinde kullanilan `mutable` keywordu farkli bir anlam ifade etmektedir.

[mutable mutex lock ornegi](res/src/class_mutable01.cpp)


### **Reference Qualifiers**
Bir sinifin non-static member fonksiyonlari, eger constness ile ilgili bir kisitlama yok ise, hem `lvalue expr` hemde `rvalue expr` sinif nesneleri ile cagrilabilir.
<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
class Myclass {
public:
  void foo();
  void bar();
};
```
```C++
Myclass mx;
mx.foo();
mx.func();

Myclass{}.foo();
Myclass{}.bar();
```
</details>
<!--  -->


Ancak oyle durumlar var ki;

  1. `rvalue expr` olan sinif nesneleri icin fonksiyonun cagrilmasini engellemek  
  2. `rvalue expr` olan ve `lvalue expr` olan sinif nesneleri icin ayri implementasyonlar olusturmak

istiyoruz.

```C++
class Myclass {
public:
  void foo() &;         // L value reference qualifier
  void bar() &&;        // R value reference qualifier
  void baz() const &;   // const L value reference qualifier
  void bax() const &&;  // const R value reference qualifier
                        //    Boyle bir qualifier'a mantiksal olarak ihtiyac olmasa da
                        //    teknik olarak yapilabilir
};
```
```C++
Myclass m;
m.foo();            // gecerli
std::move(m).foo(); // gecersiz: std::move(m) ifadesi rvalue expr ancak foo lvalue qualified
Myclass{}.foo();    // gecersiz: Myclass{} ifadesi rvalue expr ancak foo lvalue qualified

m.bar();            // gecersiz: m bir lvalue expr ancak bar rvalue qualified
Myclass{}.bar();    // gecerli
std::move(m).bar(); // gecerli

const Myclass cm;
cm.bax();           // gecersiz: cm bir lvalue expr ancak bax const rvalue qualified
std::move(cm).bax();// gecerli
```

* Ref qualifiers, fonksiyon imzasina dahil olmasi nedeniyle fonksiyon overloadu olarak kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    void func() &;        // (1) lvalue ref qualifier
    void func() const &;  // (2) const lvalue ref qualifier
    void func() &&;       // (3) rvalue ref qualifier
  };
  ```
  ```C++
  Myclass m;
  const Myclass cm;
  
  m.func();               // calls (1)
  cm.func();              // calls (2)
  Myclass{}.func();       // calls (3)
  ```
  </details>
  <!--  -->
  
* Ref-qualified olmayan bir fonksiyon ile ref-qualified olan bir fonksiyon birlikte bir overload olusturamaz. Boyle bir durumda sentaks hatasi olusur.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    void func();
    void func() &;  // sentaks hatasi
  };
  ```
  </details>
  <!--  -->
  
  
* Ref qualifiers, operator overload'lari ile birlikte kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass{
  public:
    Myclass& operator=(const Myclass&) & = default;
  };
  ```
  ```C++
  Myclass x;
  Myclass{} = x;    // gecersiz: Cunku operator= fonksiyonu lvalue qualified
  ```
  </details>
  <!--  -->
  
  