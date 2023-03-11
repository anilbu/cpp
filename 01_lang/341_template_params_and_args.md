## template parameters

Derleyicinin uretecegi kodda bazi varliklara karsilik gelen parametrelere **template parameter** denir. Bu parametreler karsilik gelen argumanlara **template argument** denir.

### template parameter categories
--------------------------------
1. **type parameter** *(tur parametresi)*
   Derleyicinin uretecegi kodda bir yada birden fazla yerde kullanilabilecek **bir turu** ifade eder. `typename` yada `class` anahtar sozcugu ile belirtilir.
   
   Ornekte `T` ve `U` ifadeleri birer type parameterdir.
   ```C++
   template <typename T, typename U>
   class Myclass {
     T mx;
     U my;
   };
   ```
   `int` `T`ye karsilik, `double` `U` ya karsilik gelen template argumanlaridir.
   ```C++
   Myclass<int, double>
   ```
2. **non-type parameter**  *(sabit parametresi)*
  Derleyicinin uretecegi kodda bir yada birden fazla yerde kullanilabilecek **bir sabit degeri** ifade eder.
    * Tamsayi turleri
    * Pointer turleri
    * Referance turleri
    * Gercek sayi turleri [C++20]
   
   Ornekte `x` ifadesi bir non-type parameterdir.
   ```C++
   template<int x>
   class Myclass {
     int ival = x;
   };
   ```
   `x`e karsilik gelen `10` bir template argumanidir.
   ```C++
   Myclass<10>
   ```

3. **template parameter**
   <!-- TODO ilgili konular islendikten sonra ileride anlatilacak... -->
   ```
   
   
   
   
   ```
   

## template arguments
Bir template parametresine karsilik gelebilecek template argumani belirtmek icin 3 farkli mekanizma bulunmaktadir:
* template argument deduction  
* template explicit arguments  
* default template argument  

Template parametrelerine karsilik verilebilecek argumanlara kisitlama uygulanabilmektedir.
*Sadece belirli turler ile kullanilmasini saglayabilir miyiz?* [[bknz: concepts ](<!-- TODO -->)]

### template argument deduction  
--------------------------------
> [auto type deduction](110_type_deduction.md#auto-type-deduction) ile hemen hemen ayni. 

* Eger cikarim yapilamaz ise, sentaks hatasi olusur.
* [C++17] class template argument deduction (CTAD)

**template type deduction ile auto type deduction arasindaki farklar**

* `initializer_list` icin template type deduction ile cikarim yapilamamaktadir:
  ```C++
  template<typename T>
  void func(T x){}
  ```
  ```C++
  auto x = {1, 3, 5, 7, 9}; // auto = initializer_list<int>
  func({1, 3, 5, 7, 9});    // sentaks hatasi
  ```

* template type deduction basarili olmak zorunda degildir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template<typename T>
  void func1(int x)
  {
  }
  
  func1(12); // T kullanilmadigi icin deduction yapilamadi
  ```
  ```C++
  template<typename T>
  T func2()
  {
  }

  func2();   // T kullanilmadigi icin deduction yapilamadi
  ```
  ```C++
  template<typename T>
  void func(T x, T y);
  
  func(12, 3.4);    // ambiguity: T int mi double mi?
  ```
  </details>
  <!--  -->
  
  
> :triangular_flag_on_post: 
> Derleyicinin template karsiligi nasil bir cikarim yaptiginin compile-time'da gosterimi:
> ```C++
> template <typename T>
> class TypeTeller;
> 
> template <typename T>
> void func(T&)
> {
>   TypeTeller<T> x;    // incomplete oldugu icin tip bilgisi ile hata mesaji verecek.
> }
> ```

[Soru](sorular/soru14.cpp)
[Ornek: std::size](res/src/template_type_deduction01.cpp)

<!-- 
**Ornekler**
  
* ```C++
  template <typename T>
  void func1(T);
  
  template <typename T>
  void func2(T* p);
  
  template <typename T>
  void func3(T** p);
  ```
  ```C++
  int x = 10;
  int* p {&x};
  int** ptr = &p;
  
  func1(x);    // T = int
  func1(p);    // T = int*
  func1(ptr);  // T = int**
  
  func2(p);    // T = int,  p = int*
  func2(ptr);  // T = int*, p = int**
  
  func3(ptr);  // T = int,  p = int**
  ```
* ```C++
  template <typename T, typaneme U>
  void func(T (*)(U));
  
  double foo(int);
  ```
  ```C++
  func(foo);      // T = double, U = int
  ```
-->
  
* Bir fonksiyonun geri donus degeri yada parametresinin turu biliniyor ise `{}` ile o sinif default init edilerek kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  int x = {};
  int y = int{};
  ```
  ```C++
  int foo(int x)
  {
      return {};
  }
  
  auto i = foo({});       // x = 0, i = 0
  ```
  ```C++
  std::string foo(std::string x)
  {
      std::cout << "x.size() = " << x.size() << '\n';
      return x;
  }
  
  auto s = foo({});
  std::cout << "s.size() = " << s.size() << '\n';
  ```
  ```C++
  template <typename T>
  void func(T x, T y);
  
  class Myclass{};
 
  func(12, {});     // T = int, x = int, y = int
  func(m1, {});     // T = Myclass, x = Myclass, y = Myclass
  ```
  </details>
  <!--  -->
  
* template parametresine bagli bir nested type'dan bahsedilmek isteniyor ise, **typename** *(`class` degil)* kullanilmalidir. Aksi halde template parametresinin turune ait bir **static veri elemani** aranmaktadir.
  ```C++
  class Myclass {
  public:
    using value_type = int;
    struct Node {};
    static inline constexpr int value = 10;
  };
  
  template<typename T>
  void func(T x) 
  {
    T::value;                 // T sinifinin static veri elemani
    typename T::Node x;       // T::Node turunden x degiskeni
    typename T::value_type y; // T::value_type turunden y degiskeni
  }
  ```
  ```C++
  Myclass::value_type v;  
  Myclass::Node node;  
  ```
  
  > :triangular_flag_on_post: 
  > [C++20] ile template parametresine bagli nested type'lardan bahsedildiginde, bazi durumlarda `typename` anahtar sozcugunun kullanilma zorunlulugu kaldirildi.
  > ```C++
  > template <typename T>
  > void func(T x) 
  > {
  >   // using mtpye = typename T::value_type;
  >   using mtpye = T::value_type;
  > }
  > ```
  
* `operator()` operandinin **callable** oldugu durumlar:
  ```C++
  template <typename F>
  void func(F f)
  {
    f();
  }
  ```
  1. Function pointer
     <details>
     <summary><b>Ornek</b> (Click to expand)</summary>
     
     ```C++
     void foo(int x) {
       std::cout << "foo(int) x = " << x << '\n';
     }
     ```
     ```C++
     func(foo);  // F = void (*)(int)
     ```
     </details>
     <!--  -->
  
  2. `operator()` fonksiyonu overload edilmis bir sinif
     <details>
     <summary><b>Ornek</b> (Click to expand)</summary>
     
     ```C++
     class Functor {
     public:
       void operator()(int x) {
         std::cout << "Functor::operator()(int) x = " << x << '\n';
       }
     };
     ```
     ```C++
     func(Functor{});  // F = Functor
     ```
     </details>
     <!--  -->
  

* Derleyici, template instantiation yaparken uretilen kodu tekrar kontrol eder.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  Asagidaki kodun legal olma ihtimali var: `operator++` ve `operator()` fonksiyonlari overload edilmis bir Functor sinif
  ```C++
  template <typename T>
  void func(T x)
  {
    ++x;
    x.foo();
  }
  ```
  </details>
  <!--  --> 
  
  [Soru](sorular/soru16.cpp)

* **partial ordering rules**: Birden fazla template secilebilmesi durumunda daha specific olan secilir. 
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  void func(T x)
  {
    std::cout << "func<T>("<< x << ")\n";
  }
  
  template <typename T>
  void func(T* x)
  {
    std::cout << "func<T*>("<< x << ")\n";
  }
  
  template <typename T>
  void func(T** x)
  {
    std::cout << "func<T**>("<< x << ")\n";
  }
  
  template <typename T, int sz>
  void func(T (&x)[sz])
  {
    std::cout << "func<T[" << sz << "]>("<< x << ")\n";
  }
  ```
  ```C++
  int x { 10 };
  int* p = &x;
  
  func(x);    // calls func<T>()    T = int
  func(&x);   // calls func<T*>()   T = int
  func(p);    // calls func<T*>()   T = int
  func(&p);   // calls func<T**>()  T = int
  ```
  </details>
  <!--  -->
  

* template parametrelerinin scope'u bildirildigi template'de gecerlidir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  // declaration
  template<typename T>
  void func(T x);
  
  // definition
  template<typename U>
  void func(U x)
  {
    
  }
  ```
  </details>
  <!--  -->
  
### explicit template argument
--------------------------------
Derleyici tarafindan cikarim yapilmadan, tur bilgisinin acik olarak verilmesi.

```C++
template <typename T>
void func(T x) 
{
}
```
```C++
float f = 3.14f;

func<int>(12);      // T = int
func(f);            // T = float
func<double>(f);    // T = double
```

* explicit argumanlar ve deduction mekanizmasi birlikte kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template<typename T, typename U, typename W>
  T func(U x, W y)
  {
      return x + y;
  }
  ```
  ```C++
  func<double>(1, 4.5); // T = double, U = int, W = double
  ```
  </details>
  <!--  -->
  
* Derleyicinin cikarim yapamadigi durumlarda explicit olarak template argumani belirtilmek zorundadir.

* Bir fonksiyonun geri donus turunu belirtmek icin farkli yontemler izlenebilir:
  1. Ucuncu bir typename eklenebilir
     <details>
     <summary><b>Ornek</b> (Click to expand)</summary>
     
     ```C++
     template <typename Result, typename T, typename U>
     Result sum(T x, U y)
     {
        return x + y;
     }
     ```
     ```C++
     int ival {12};
     double dval { 3.14 };
     sum<double>(ival, dval);
     ```
     </details>
     <!--  -->
     
  2. trailing return type kullanilabilir
     <details>
     <summary><b>Ornek</b> (Click to expand)</summary>
     
     ```C++
     // decltype(x+y) sum(T x, U y) ifadesinde x ve y scope problemi olmasi nedeniyle
     // trailing return type kullanilabilir
     template <typename T, typename U>
     auto sum(T x, U y) -> decltype(x+y)
     {
        return x + y;
     }
     ```
     ```C++
     int ival {34};
     double dval { 3.14 };
     sum(ival, dval);
     ```
     </details>
     <!--  -->
     
  3. auto return type kullanilabilir
     <details>
     <summary><b>Ornek</b> (Click to expand)</summary>
     
     ```C++
     template <typename T, typename U>
     auto sum(T x, U y)
     {
        return x + y;
     }
     ```
     ```C++
     int ival {34};
     double dval { 3.14 };
     sum(ival, dval);
     ```
     </details>
     <!--  -->
     
* Uretilecek fonksiyon sayisini azaltmak amaciyla explicit olarak tur verilebilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  void func(T) {
    std::cout << "func(" << typeid(T).name() << ")\n";
  }
  ```
  ```C++
  func(3.14);
  func<double>(3.14f);
  func<double>(12LL);
  ```
  </details>
  <!--  -->
  
   
* template fonksiyonlar non-template fonksiyonlar ile overload edilebilir.
  Once fonksiyon overloadi varsa, yoksa templete instantiation yapilir.
  ```C++
  template <typename T>
  void func(T) {
    std::cout << "func<T>(" << typeid(T).name() << ")\n";
  }
  
  void func(int x) {
    std::cout << "func(int)\n";
  }
  ```
  ```C++
  func(12.4);    // func<double>(double) cagrilir.
  func(12);      // func(int) cagrilir
  func<int>(12); // func<int>(int) cagrilir
  func<>(12);    // func<int>(int) cagrilir
  ```
  Oyle bir fonksiyon olusturun ki, argumanlarda implicit donusum mumkun olmasin:
  ```C++
  template<typename T>
  void func(T) = delete;
  
  void func(int);
  ```
  ```C++
  func(12);     // gecerli
  func(12.1);   // gecersiz call to a deleted function
  func("abc");  // gecersiz call to a deleted function
  func('a');    // gecersiz call to a deleted function
  ```

[Ornek](res/src/func_templ01.cpp)
  
### default template arguments
------------------------------
Bir template parametresine karsilik olarak template argumaninin varsayilan olarak bildirilmesidir. 

```C++
template <typename T = int>
struct Myclass {
  Myclass() {
    std::cout << "typeid(T).name() = " << typeid(T).name() << '\n';
  }
};
```
```C++
Myclass<double> m1;     // T = double
Myclass<> m2;           // T = int
Myclass m3;             // T = int (CTAD)
```

> :warning: 
> Function template'leri icin default template argumanlari C++11 ile dile eklenmistir. Daha oncesinde sadece sinif sablonlarinda kullanilabiliyordu.

* Template tur cikarimi fonksiyonun varsayilan argumana karsi yapilamaz. Varsayilan fonksiyon argumani ile varsayilan template argumani karistirilmamalidir.
  ```C++
  template <typename T>
  void func(T x = 0);
  ```
  Asagidaki `func()` cagrisinda `T` turu `void func(void)` olarak yapilacagi icin sentaks hatasina neden olur.
  ```C++
  func();   // sentaks hatasi: T int degil!
  ```
  
* Default template argumani icerisinde baska bir template parametresi de kullanilabilir:
  ```C++
  template<typename T, typename U = T>
  class Myclass;
  
  Myclass<int> x;      // x = Myclass<int, int>
  ```
  ```C++
  template<typename T, typename U = T*>
  class Myclass;
  
  Myclass<int> x;      // x = Myclass<int, int*>
  ```
  ```C++
  template <typename T>
  struct Nec;
  
  template <typename T, typename U = Nec<T>>
  struct Myclass;
  
  Myclass<int> x;      // x = Myclass<int, Nec<int>>
  ```
  
* Fonksiyonlarda kullanilan varsayilan argumanlarinda oldugu gibi, template varsayilan argumanlarinda da eger bir parametre default arguman almis ise, sagindaki tum parametreler de varsayilan argumana sahip olmalidir.
  ```C++
  template <typename T = int, typename U> // gecersiz
  class Myclass;  
  ```
  
* Template varsayilan argumani ile function varsayilan argumani birlikte kullanilabilir.
  ```C++
  struct Myclass;
  
  template <typaname T, typename U = Myclass>
  void func(T x, U y = U{}) 
  {
  }
  ```
  ```C++
  func(12);         // T = int, U = Myclass oldugu icin: func(12, Myclass{})
  func(12, Nec{});  // T = int, U = Nec     oldugu icin: func(12, Nec{})
  ```



### CTAD [C++17]
*(class template argument deduction)*

Sinif sablonlarinda argument type deduction yapilabilmesini saglayan bir ozelliktir. [C++17]'e kadar CTAD sinif sablonlari icin kullanilamiyordu.

* ```C++
  template <typename T>
  class Myclass {
  public:
    Myclass(T);
  };
  ```
  ```C++
  Myclass x(13);  // x = Myclass<int>
  ```

* ```C++
  std::vector x{ 1, 3, 5, 7, 9};    // x = vector<int>
  ```

* Ctor'a gonderilen argumandan hareketle template parametresine cikarim yapilir:
  ```C++
  template <typename T = double>
  struct Myclass {
    Myclass(T);
  };
  ```
  ```C++
  Myclass x = 10;           // Myclass<int>     (CTAD devreye girdi)
  Myclass<> y = 10;         // Myclass<double>  (CTAD devreye girmedi, default template parameter kullanildi)
  Myclass<double> z = 10;   // Myclass<double>
  ```
<!-- TODO Ileride detayli anlatilacak -->