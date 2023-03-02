## Move Members

### **Move Semantics**
Bir nesneyi hayata getirirken, baska bir objeden olusturmak istendiginde; kopyalama yada atama yontemlerinden biri kullanilmaktaydi. Kaynak yonetimi yapmasi gereken sinif turunden nesneler, tipik olarak **deep copy** yapilarak kopyalanir/uretilir.
```C++
T x = other;    // kopyalama
x = another;    // atama
```

Kaynagi kopyalanacak olan nesnenin, baska bir kod tarafindan kullanilmadigini (hayatinin bitmekte oldugunu) biliyorsak; bu nesnenin kaynagini **gereksiz yere kopyalamak** yerine kopyalayan nesneye **tasinabilir**. *Kisaca, hayati bitmekte olan bir nesnenin kaynagi calinabilir.* Kaynagi calinmis bir nesnenin hayati sonlanirken kaynagi geri vermemesi gerekmektedir.

**Neden daha once boyle birsey yapilamiyordu?**
Derleyicinin kaynak koda bakarak, `=`'in saginda bulunan ifadenin bir sinif nesnesi oldugunu ve bu nesnenin hayatinin bitmekte olup olmadigini anlayabilmesi gerekmektedir. Derleyicinin bir nesnenin hayatinin bitmekte oldugunu anlayabilmesi icin dile *temel syntax seviyesinde* [rvalue reference](100_ref_semantics.md#rvalue-references) kavrami eklenmistir.

> :pushpin: 
> `const T&` ve `T&&` arasinda olusan overload arasinda eger arguman **lvalue expr** ise `const T&` overloadu, **rvalue expr** ise `T&&` overloadu secilir. [[bknz: function overload resolution](145_function_overload_resolution.md#ozel-durumlar)]

> :pushpin: 
> rvalue expr $\equiv$ (prvalue expr $\cup$ xvalue expr)

Bu kural ctor ve atama operatorleri icin de gecerlidir:
```C++
class Myclass {
    Myclass();
    
    Myclass(const Myclass&);            // copy ctor
    Myclass(Myclass&&);                 // move ctor
    
    Myclass& operator=(const Myclass&); // copy assignment
    Myclass& operator=(Myclass&&);      // move assignment
};
```
```C++
Myclass foo();

Myclass x;
Myclass y = x;      // x ifadesi bir lvalue expr olmasi nedeniye copy ctor cagrilacak
Myclass z = foo();  // foo() ifadesi bir rvalue expr olmasi nedeniye move ctor cagrilacak

y = x;              // x ifadesi bir lvalue expr olmasi nedeniye copy assign cagrilacak
y = foo();          // foo() ifadesi bir rvalue expr olmasi nedeniye move assign cagrilacak
```

Asagidaki kod orneginde; normalde `y` nesnesi olusturulurken copy ctor cagrilacaktir. Ancak `x`'i gozden cikarip `y`'yi hayata getirirken `x`'in kaynagini calmasini istiyoruz.
```C++
Myclass x;
Myclass y = x;
```
Eger `x` ifadesini bir sekilde `rvalue expr`'a cevirebilirsek move ctor cagrilacaktir.

1. Tur donusum operatoru kullanmak
   ```C++
   Myclass y = static_cast<Myclass&&>(x);   // static_cast<Myclass&&>(x) ifadesi bir rvalue expr
   ```
2. `std::move` fonksiyonu
   
#### **`std::move` fonksiyonu**
`std::move` fonksiyonu, bir `lvalue expr`'i `rvalue expr`'a ceviren bir fonksiyondur.

**Sadelestirilmis Ornek Implementasyon**
```C++
template<typename T>
constexpr T&& move(T&& t) noexcept { 
    return static_cast<T&&>(t);
}
```

```C++
Myclass y = std::move(x);   // x ifadesi bir lvalue expr iken, std::move(x) ifadesi bir rvalue expr
```
> :warning:   
> *Move doesn't move! -Scott Meyers*
> 
> `std::move` fonksiyonun ismi *move* olmasina ragmen tasima yapmaz, sadece *casting* yaparak degerin value kategorisini degistirir. Tasima islemini **move member function**lar yapar!

* primitive turler icin tasima islemi kopyalamadir.
  ```C++
  int y = 10;
  int x = y;
  int x = std::move(y); // y'nin degeri x'e kopyalanir
  ```


### Move Constructor
[cppreference.com](https://en.cppreference.com/w/cpp/language/move_constructor)  

A move constructor of `class T` is a non-template constructor whose first parameter is `T&&`, `const T&&`, `volatile T&&`, or `const volatile T&&`, and either there are no other parameters, or the rest of the parameters all have default values.

```C++
class Myclass {
  A ax;
  B bx;
  C cx;
};
```
Derleyicinin urettigi default move ctor:
```C++
Myclass(Myclass&& other) : ax(std::move(other.ax)),
                           bx(std::move(other.bx)),
                           cx(std::move(other.cx))
{
}
```
[Ornek: String sinifi move ctor](res/src/smf_move_ctor01.cpp)

### Move Assignment

```C++
class Myclass {
  A ax;
  B bx;
  C cx;
};
```
Derleyicinin urettigi default move assignment
```C++
Myclass& operator=(Myclass&& other)
{
  ax = std::move(other.ax);
  bx = std::move(other.bx);
  cx = std::move(other.cx);
  return *this;
}
```
[Ornek: String sinifi move assignment](res/src/smf_move_ctor02.cpp)

-------------


> :warning:   
> Move memberlar, kaynagini caldigi nesneyi **gecerli bir durumda** (in a valid state) birakmalidir. Kaynagi calinmis bir nesnenin, atama yolu ile **tekrardan kullanilabilme** ihtimali vardir!
> ```C++
>   String(String&& other) : mlen{other.mlen}, mp{other.mp}
>   {
>       // nesneyi valid bir state'de birakilmasi gerekmektedir.
>       other.mlen = 0;
>       other.mp = nullptr;
>   }
>   
>   String& operator=(String && other) 
>   {
>       // kendi kaynagini release et
>       std::free(mp);
>       
>       // tasima
>       mlen = other.mlen;
>       mp = other.mp;
>          
>       // other'i valid state'de birak
>       other.mlen = 0;
>       other.mp = nullptr;
>       
>       return *this;
>   }
> ```

### Dikkat edilmesi gereken onemli noktalar

* Bir nesneyi `T&&`'e baglamak, o nesnenin tasindigi anlamina gelmez! Tasimanin gerceklesmesi icin move memberlardan biri calismalidir!
  ```C++
  string str(20'000, 'A');
  std::cout << "str.size() = " << str.size() << '\n';

  string&& r = move(str); // move gerceklesmez, sadece rref'e cast'in yapilir.
  std::cout << "str.size() = " << str.size() << '\n';

  string s2(move(str));   // move islemi gerceklesir
  std::cout << "str.size() = " << str.size() << '\n';
  ```

* `T&&` isimleri, `lvalue expr`dir! Data type ile value category'i karistirmayin! 
  ```C++
  void func1(const std::string& s) 
  {
    // argumanin value kategorisinden bagimsiz olarak
    // s ifadesi bir lvalue expr olmasi nedeniyle copy ctor calisir.
    std::string str(s); // str icin copy ctor
  }
  
  void func1(std::string&& s) 
  {
    // argumanin value kategorisinden bagimsiz olarak 
    // s ifadesi bir lvalue expr olmasi nedeniyle 
    // std::move fonks kullanilmalidir!
    std::string str(std::move(s));  // str icin move ctor
  }
  ```
  ```C++
  std::string s(10'000, '+');
  func(s);  // ref semantigi, kopyalama yada tasima yok
  ```
  
* `const` bir nesnenin kaynagini calamazsiniz ve **calmamalisiniz**! Dilin kurallari bu duruma engel olur.
  ```C++
  class Myclass{
  public: 
    Myclass() = default;
    Myclass(const Myclass&) {
        std::cout << "copy ctor\n";
    }
  
    Myclass(Myclass&&) {
        std::cout << "move ctor\n";
    }
  };
  ```
  ```C++
  Myclass x;
  const Myclass cx;
  
  Myclass y1 = std::move(x);  // move ctor cagrildi
  Myclass y2 = std::move(cx); // copy ctor cagrildi: cunku arguman bir const nesne!
  ```
  
  Cunku `std::move` fonksiyonu `const` bir nesne aldiginda geri donus degeri `const qualified rvalue expr` olmasi nedeniyle, function overload resolution'a gore `copy ctor` cagrilir.
  
  > :pushpin: 
  > `rvalue expr`lar, `const lvalue ref`'lere baglanabilir! [[bknz: rvalue references](100_ref_semantics.md#rvalue-references)]
  
  
**Ornekler**
* ```C++
  class Myclass {};
  
  void func(const Myclass &);   // (1)
  void func(Myclass &&);        // (2)
  ```
  ```C++
  Myclass m;
  const Myclass cm;
  
  func_1(m);              // calls (1)
  func_1(std::move(m));   // calls (2)
  func_1(cm);             // calls (1)
  func_1(std::move(cm));  // calls (1)
  ```
* ```C++
  class Myclass {};
  
  void func(const Myclass &);   // (3)
  void func(Myclass &&);        // (4)
  void func(const Myclass &&);  // (5): pratikte ihtiyac duyulmacak bir overload eklendi (const rvalue ref)
  ```
  ```C++
  func_2(m);              // calls (3)
  func_2(std::move(m));   // calls (4)
  func_2(cm);             // calls (3)
  func_2(std::move(cm));  // calls (5)
  ```