## Array-like siniflar

Bir veriyapisini temsil eden siniflardir.

* `std::vector`
* `std::string`
* `std::array`
* `std::deque`
* `std::set`
* `std::map`

## Index `[]` operator fonksiyonunun overload edilmesi

Tipik olarak array-like siniflarda veri elemanlarina erisim icin overload edilir.

* `[]` operatoru aslinda bir pointer operatorudur.  
  `a[i]` ile `*(a + i)` ayni anlam ifade etmektedir.  
  `a[i]` ile `i[a]` ayni anlam ifade etmektedir. *(Siniflar icin gecerli degil!)*  

* Member function operator olmak zorundadir.  
  `obj[i]` == `obj.operator[](i)`

* `obj[i]` bir lvalue expr oldugundan dolayi bir `T&` geri dondurmelidir.  
  *Aksi halde elemana atama yapilamaz.*

* Tipik olarak array-like siniflarda `[]` operatoru fonksiyonu overload edilirken 2 tane overload yazilir:
  1. `const` olmayan nesneler icin  
     Geri donus tipi `T&` turundendir.  
     ```C++
     T& operator[](std::size_t);
     ```
  2. `const` nesneler icin  
     Geri donus tipi `const T&` turundendir.  
     ```C++
     const T& operator[](std::size_t) const;
     ```


```C++
class String { 
public:
    ...
    char& operator[](std::size_t idx);              // (1)
    const char& operator[](std::size_t idx) const;  // (2)
    ...
}

String name;
const String cname;

name[2] = 'A';   // legal:   (1) cagrildi
cname[2] = 'A';  // illegal: (2) cagrildi
```

[Ornek: Name sinifi](res/src/15_name.cpp)

## Pointer-like siniflar
Nesneleri pointer degisken gibi kullanilan siniflardir. Bir pointer interface'i sunarlar.

```C++
  operator*
  operator->
  operator++ ve operator--
```

Tipik olarak 2 kategorisi vardir:
1. **Iterator**: Nesnelerin konum bilgisini barindirmak
   ```C++
   vector<string> ivec{ "ali", "ayse", "ahmet"};
   auto it = ivec.begin();     // vector<string>::iterator
   
   cout << *it << '\n';  // prints "ali"
   
   ++it;
   cout << *it << '\n';          // prints "ayse"
   cout << it->size() << '\n';   // prints 5
   ```

2. **smart pointers**: Dinamik omurlu bir nesnenin hayatini kontrol etmek
   ```C++
   std::shared_ptr<int> sp = std::make_shared<int>(0);
   cout << *sp << '\n';
   ```
   
## Icerik `*` ve ok operatoru `->` fonksiyonlarinin overload edilmesi
Tipik olarak pointer-like siniflarin interface'ini implement etmek icin overload edilir.

```C++
#include <memory>

std::unique_ptr<string> uptr { new std::string };
uptr->size();   // uptr.operator->()->size();
```
```C++
class Ptr {
    A& operator*();
    A* operator->();
};

Ptr p;

*p;         // p.operator*()
p->foo();   // p.operator->()->foo();
```

* `*` operator fonskiyonu bir nesneye erisim saglamasi nedeniyle bir lvalue expr olmasi gerekiyor. Dolayisiyla geri donus turu `T&` olmalidir.

* `->` operatoru binary bir operator olmasina ragmen unary operator gibi overload edilir.

* `->` operatoru `T*` yada `->` overloaduna sahip bir sinif turunden geri donmelidir.  
  *Aksi halde operatoru kullanmanin bir yolu bulunmamaktadir.*
  ```C++
  p.operator->() -> foo();
                 ^ buraya eklenen operatorden dolayi
  ```
  ```C++
  class A{
  public:
      void foo();
      void bar();
  };
  
  class B {
      A* operator->();
  };
  
  class PtrA {
      A& operator*();
      A* operator->();
  };
  
  class PtrB {
      B operator->();
  };
  
  PtrB pb;
  pb->bar();   // gecerli: pb.operator->().operator->() -> bar();
               // pratikte kullaniliyor ancak cok sik degil
  ```

> **Ornek**  
> 
> * Ismi `SmartPtr` olan bir sinif olusturulacak
> * `SmartPtr` turunden olan nesneler `T*` turunden pointerlar gibi davranacak.  
>   
>   Yani;
>     * `T*` yerine `SmartPtr` nesnesi kullanilacak
>     * `SmartPtr` nesnesinin hayati bittiginde onun (sozde) gosterdigi `T` nesnesi delete edilecek
> 
> [16_smart_ptr.cpp](res/src/16_smart_ptr.cpp)


## Fonksiyon cagri `()` operator fonksiyonunun overload edilmesi
*En sik overload edilen operatorlerden biridir! Genelde generic programlama araclari ile guclu olarak kullanilmaktadir.*

* `func()` ifadesi ile bir fonksiyon cagriliyor ise hangi ihtimaller soz konusu olabilir?

    C dilinde;
    1. func, bir **fonksiyon ismi** olabilir.
    2. func, bir **fonksiyon pointer**i olabilir.
    3. func, **functional macro** olabilir.

    C++ dilinde; -ek olarak-

    4. func, **function call operatorunu** overload etmis bir **sinif nesne**si olabilir.  
       *Boyle siniflara `functor class` yada `function object` olarak isimlerilir.*
       ```C++
       func(10);    // func.operator()(10);
       ```

> **callable**  
> `()`' operatorunun operandi oldugunda fonksiyon cagrilmasini saglayan varliklara genel olarak *callable* denir.

```C++
class Functor{ 
public: 
    ...
    void operator()();
    ...
};

Functor fn;
fn();  // fn.operator()();
```

* `()` operatoru **sadece member function** olarak overload edilebilir.
* Parametreleri ve geri donus turu normal fonksiyonlar gibi verilebilmektedir.
* Bir sinifin birden fazla `()` operator overloadu olabilir.  
  *Normal fonksiyonlar gibi kendi icinde overload edilebilir.*
* Normal fonksiyonlar gibi **default arguman** alabilir.  
  *Diger operator overload fonksiyonlari default arg alamazlar!*

```C++
class Nec {
public:
  void operator()() {
    cout << "void operator()()\n";
  }
  void operator()(int) {
    cout << "void operator()(int)\n";
  }
  void operator()(int, int) {
    cout << "void operator()(int, int)\n";
  }
  void operator()(double=0.0) {
    cout << "void operator()(double)\n";
  }
};

Nec nec;
nec();
nec(10)
nec(3, 4)
nec(3.5);
```

**Motivasyon**
Bir sinif nesnesi olmasi nedeniyle kendisi bir **state** bilgisine sahip.  
*Ayni sinif turunden nesneler ayni state bilgisine sahip olmak zorunda degil!*  
[Ornek: MRandom sinifi](res/src/16_func_op_mrandom.cpp)
```C++
MRandom rand1{100, 500};
MRandom rand2{900, 910};
...
std::cout << "rand1 ile " << rand1.get_call_count() << " sayi uretildi.\n";
std::cout << "rand2 ile " << rand2.get_call_count() << " sayi uretildi.\n";
```

*callable*lar generic programlama ile sikca kullanilmaktadir.