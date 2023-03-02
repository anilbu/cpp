# Virtual Dispatch

C++'da calisma zamaninda hangi fonksiyonun cagrilmasi gerektiginin belirlenmesini saglayan mekanizmaya **virtual dispatch** denir. Alt katmandaki kodlarin ust katmandaki kodlara bagimlilik olusturmadan genisletilebilir kod yazilabilmesini saglar.

[Ornek](res/src/virtual_dispatch01.cpp)


## Overriding a member function
Taban sinifin `virtual` anahtar sozcugu ile bildirilmis fonksiyonunun, turemis siniflar tarafindan `override` edilmesi belirli syntax'a uygun olarak yapilmak zorundadir.

```C++
class Base {
public:
    virtual void func();
};

class Der : public Base {
public:
    void func() override;
};
```

* Turemis sinif, taban sinifin bir virtual fonksiyonunu override etmek icin **hem imzasi hem de geri donus degeri turu ayni** olan bir fonksiyon bildirmek zorundadir.
  *Istisna: [Covariance](#covariance-variant-return-type)*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Base {
  public:
    virtual void func(int);
  };
  
  class Der : public Base {
  public:
    void func(int);
  };
  ```
  </details>
  <!--  -->
  
* Override edilmis bir fonksiyon bildiriminde `virtual` anahtar sozcugu kullanilsa da kullanilmasa da artik virtual fonksiyondur.

### `override` contextual keyword

Derleyicinin bir fonksiyonun override edildigini dogrulama amaciyla kullanilan bir [contextual keyword](020_temel_kavramlar.md#contextual-keyword)'tur.

* Taban sinifin non-virtual bir fonksiyonunu *yada var olmayan bir fonksiyonunu* override edilmeye calisilmasi durumunda, sentaks hatasi olusturur.
* Fonksiyon imzasina dahil degildir.

> :triangular_flag_on_post: 
> `override` kullanimi opsiyoneldir, ancak kullanilmasi sik yapilan hatalardan kacinmak icin **tavsiye edilir**.
>  <details>
>  <summary><b>Bu hatalardan bazilari:</b> (Click to expand)</summary>
>  
>  ```C++
>  class Base {
>  public:
>    void foo(int);
>    virtual void bar(int);
>  };
>  ```
>  **Case 1**: `Base::foo` non-virtual fonksiyonunun yanlislikla override edilmek istenmis oldugunu varsayin:
>  <details>
>  <summary><b>Ornek</b> (Click to expand)</summary>
>  
>  ```C++
>  class Der : public Base {
>  public:
>    void foo(int);  // sentaks hatasi yok, override degil, overload da degil
>  };
>  ```
>  </details>
>  <!--  -->
>  
>  **Case 2**: `Base::bar` virtual fonksiyonunun override edilmek istenmis oldugunu varsayin:
>  <details>
>  <summary><b>Ornek</b> (Click to expand)</summary>
>  
>  ```C++
>  class Der : public Base {
>  public:
>    void bar(unsigned int); // imza farkli oldugu icin override degil
>                            // overload da degil
>                            // sentaks hatasi da yok
>  };
>  ```
>  </details>
>  <!--  -->
>  
>  **Case 3**: `Base::baz` fonksiyonunun override edilmek istenmis oldugunu varsayin
>  <details>
>  <summary><b>Ornek</b> (Click to expand)</summary>
>  
>  ```C++
>  class Der : public Base {
>  public:
>    virtual void bar(unsigned int); // imza farkli oldugu icin override degil
>                                    // ve istem disi yeni bir sanal fonksiyon olusturuldu
>  };
>  ```
>  </details>
>  <!--  -->
>  
>  **Case 4**: `Base` sinifin virtual fonksiyonunun parametrik yapisi gereksinimler nedeniyle degismesi durumunda turemis siniflarda sentaks hatasi olmamasiyla birlikte override'lar da gecersiz olacaktir.
>  <details>
>  <summary><b>Ornek</b> (Click to expand)</summary>
>  
>  ```C++
>  class Base {
>  public:
>    // bar fonksiyonuna yeni bir guncelleme ile 
>    // daha once bulunmayan yeni bir double parametre eklendigini varsayin
>    virtual void bar(int, double);     
>  };
>  
>  class Der : public Base {
>  public:
>    void bar(int); // guncellemeden once override idi
>                   // ancak suanda der sinifina ait yeni bir fonksiyon haline geldi
>                   // sentaks hatasi da yok
>  };
>  ```
>  ```C++
>  Der der;
>  Base& baseref = der;
>  baseref.bar(10);        // guncellemden once Der::bar override'ina cagri yapilmaktaydi
>  baseref.bar(10, 3.14);  // guncellemden sonra Base::bar cagrisi yapilacaktir
>  ```
>  </details>
>  <!--  -->
>  </details>
>  <!--  -->
  
## Virtual dispatch uygulanan ve uygulanmayan durumlar

```C++
class Base {
public:
    virtual void func();
    
    void foo() {
      func();
    }
    
    void bar() {
      Base::func();
    }
};

class Der : public Base {
public:
    void func() override;
};
```

* Turemis sinif turunden bir nesnenin bir sanal fonksiyonuna yapilan cagri, **`Base*`** yada **`Base&`** **uzerinden** yapilmis ise virtual dispatch **her zaman uygulanir**.
  ```C++
  Der der;
  Base* baseptr = &der;
  baseptr->func();  // calls Der::func
  
  Base& baseref = der;
  baseref.func();   // calls Der::func
  ```
> :triangular_flag_on_post: 
> *`this` pointeri uzerinden  yapilan sanal fonksiyon cagrilari*

* Turemis sinif turunden bir nesne ile olusturulan bir taban sinif turunden nesne ile cagri yapilmasi durumunda **object slicing** olusmasindan dolayi virtual dispatch mekanizmasi **uygulanmaz**.
  ```C++
  Base base = der;  // legal: engel olacak bir durum yok, ancak object slicing var.
  base.func();      // calls Base::func
  ```

* Turemis sinif nesnesi ile taban sinifin fonksiyonu icerisinde sanal fonksiyonuna cagri yapiyorsa *yani `Base*` turunden olan this pointer'i uzerinden* virtual dispatch uygulanir. Ancak, **nitelenmis bir isim** ile fonksiyon cagrisinda virtual dispatch **uygulanmaz**.
  ```C++
  Der der;
  der.foo();  // foo fonksiyonu icerisinde yapilan func cagrisi Der::func()
              // Cunku foo icerisinde this pointeri Base* turundendir.
  
  der.bar();  // bar fonksiyonu icerisinde yapilan func cagrisi Base::func() 
              // Cunku func cagrisi Base:: olarak nitelendigi icin
  ```

* Taban sinifin **constructor icinde** *turemis sinif nesnesinin henuz olusturulmamis olmasindan dolayi* yapilan virtual fonksiyon cagrilarinda virtual dispatch **uygulanmaz**.
 
  Taban sinif **destructori icinde** *turemis sinif nesnesinin hayati daha once sonlanmasindan dolayi* yapilan virtual func cagrilarinda virtual dispatch **uygulanmaz**.
   ```C++
  class Base {
  public:
    Base() {
      func(); // virtual dispatch uygulanmaz.
    }
    
    ~Base() {
      func(); // virtual dispatch uygulanmaz.
    }
    virtual void func();
  };

  class Der : public Base {
  public:
    void func() override;
  };
  ``` 
* **Abstract bir taban** sinifdan *nesne olusturulamayacagi icin* **object-slicing** olusmasi durumunda sentaks hatasi olusur.  
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Car {
  public:
    virtual void start() = 0;
    virtual void run() = 0;
    virtual void stop() = 0;
  };
  
  void car_game(Car car);   // Dikkat: parametre * yada & turu degil!
  ```
  ```C++
  car_game(*create_random_car()); // sentaks hatasi
  ```
  </details>
  <!--  -->
  
  
* Turemis sinifda taban sinifin **private virtual** fonksiyonu **override edilebilmektedir**. [NVI](#non-virtual-interface) idiomunda oldukca fazla kullanilir.
  *Bir fonksiyonu override edilmesi ile access-control'un dogrudan bir iliskisi yoktur. [[bknz: static typing](290_runtime_polymorphism.md#static-typing-ve-dynamic-typing)]*
  ```C++
  class Base {
  private:
      virtual void func();
  };

  class Der : public Base {
  public:
      void func() override;
  };
  ```

* global bir fonksiyonu virtual fonksiyonmus gibi davranmasinin istendigi bir durumda global fonksiyona `friend` verilip, virtual dispatch mekanizmasindan faydalanabilir.
  ```C++
  class Car { 
  public:
    
    // ...
    
    friend std::ostream& operator<<(std::ostream& os, const Car& c) {
      c.print(os);
      return os;
    }
    
  private:
    virtual void print(std::ostream& os) const = 0;
  };
  
  void car_game(Car*)
  {
    std::cout << *p << '\n';
    
    p->start();
    p->run();
    p->stop();
  }
  ```

## Non-Virtual Interface
<!-- TODO Aciklamalari ekle -->
```C++
class Base {
public:
  void foo() {
    func();
  }
private:
    virtual void func() = 0;
};

class Der : public Base {
private:
    virtual void func() override;
};
```
```C++
Der der;
Base& baseref = der;
baseref.func();         // calls Der::func
der.func();             // syntax error: inaccessible
```
[Ornek](res/src/nvi_idiom02.cpp)

## Covariance
*Variant return type*

Override edilen bir fonksiyonun geri donus turunun, bu turden turetilmis sinif turlerinden olmasinda **covariance** *(variant return type)* denilmektedir.

* Geri donus turu, override edilen fonksiyonun return tipinden turemis bir sinif olmasi gerekmektedir.
* Geri donus turu ptr yada ref olmasi gerekmektedir.

[Ornek](res/src/covariant01.cpp)
```C++
class Base {};
class Der : public Base {};

class B {
public:
  virtual Base* create_obj();
};

class A : public B{
public:
  virtual Der* create_obj() override;
};
```
```C++
A ax;
Der* p = ax.create_obj();

B& baseref = ax;
Base* ret = baseref.create_obj();   // Gercekte foo islevi bir Der* donduruyor
```
A'nin override'i `Base*` yerine `Der*` donebilir, cunku *her `Der` bir `Base`dir*. Burada farklilik olusturan tur taban sinif virtual functioninin geri donus turunden turemis olmasidir. 


## Virtual Constructor Idiom (Clone Idiom)

C++ dilinde sadece non-static member fonksiyonlar virtual olabilmektedir.
Taban tur pointer'i ile referans edilen dinamik turden bir nesne olusturmak istenildiginde *Virtual Constructor Idion(Clone Idiom)* kullanilabilir.

> :warning: 
> global functions, static member functions, constructors virtual olamazlar. 

[Ornek](res/src/virtual_ctor_idiom01.cpp)
```C++
class Car {
public:
    // ...
    virtual Car* clone() = 0;
};

class Volvo : public Car {
private:
    // ...
    virtual Volvo* clone() override {
        return new Volvo(*this);    // copy ctor call
    }
};

void car_game(Car* p) 
{
    // *p nesnesinin dinamik turu ne ise o turden bir nesne olusturmak isteniyor:
    Car* pnew = p->clone();
    p->start();
    delete p;
}
```

## Virtual Destructor

Destructor'i virtual olmayan turemis sinif turunden bir nesne, bir taban sinif pointeri uzerinden `delete` edilirse turemis sinifta tanimlanmis dtor **cagrilmamaktadir**. Bu durum bir **UB**dir, ayrica *resource leak*'e neden olabilir.

Polymorphic siniflarin destructor'u soz konusu oldugunda; 
taban siniflar icin su ikisinden biri yapilmalidir:

* **public virtual dtor**  
  *Bu bir polymorphic nesnedir ve turemis siniflarda dtor'un override edilmesi gerekebilir!*
  ```C++
  class Base{
  public:
      virtual ~Base() = default;
  }
  ```
* **protected non-virtual dtor**  
  *Turemis sinif turunden bir nesne adresinin `delete` operatorune taban sinif pointeri uzerinden operand yapilmasi engellendi.*
  ```C++
  class Base{
  protected:
      ~Base() = default;
  }
  ```
  
> :triangular_flag_on_post: 
> Herb Sutter tarafindan ortaya atilan dilin semantik kuralidir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

[Ornek](res/src/virtual_dtor01.cpp)
```C++
class Base {
public:
    ~Base() {
        std::cout << "~Base()\n";
    }
};

class Der : public Base { 
public:
    ~Der() {
        std::cout << "~Der()\n";
    }
};
```
```C++
Der* derptr = new Der;
delete derptr;      // ~Der() cagrildi
                    // ~Base() cagrildi

std::cout << "--------------\n";

Base* baseptr = new Der;
delete baseptr;     // tanimsiz davranis
                    // sadece ~Base() cagrildi.
```
Yukaridaki durumun olmamasi icin Base'in dtoru `virtual ~Base()` olmalidir.
[Ornek](res/src/virtual_dtor02.cpp)
```C++
class Base {
public:
    virtual ~Base() {
        std::cout << "~Base()\n";
    }
};

class Der : public Base { 
public:
    ~Der() override {
        std::cout << "~Der()\n";
    }
};
```
```C++
Der* derptr = new Der;
delete derptr;      // ~Der() cagrildi
                    // ~Base() cagrildi

std::cout << "--------------\n";

Base* baseptr = new Der;
delete baseptr;     // ~Der() cagrildi
                    // ~Base() cagrildi
```
Yada `protected non-virtual` yapilarak taban sinif pointer'i uzerinden `delete` operatoruna operand yapilmasi engellenmelidir:
[Ornek](res/src/virtual_dtor03.cpp)
```C++
class Base {
protected:
    ~Base() {
        std::cout << "~Base()\n";
    }
};

class Der: public Base {
public:
    virtual ~Der() {
        std::cout << "~Der()\n";
    }
};
```
```C++
Der* derptr = new Der;
Base* baseptr = derptr;

delete baseptr;   // sentaks hatasi: Bu nesneyi taban sinif uzerinden silmeye calisma

delete derptr;      // ~Der() cagrildi
                    // ~Base() cagrildi
```
</details>
<!--  -->
