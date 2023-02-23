# Variadic templates

Tek bir template olusturularak $n$ adet template parametresine sahip olabilen templatelerin olusturulabilmesini saglayan bir aractir. 

> **Not**  
> `...` *elipsis atomu*

## Template Parameter Pack
$0$ yada $n$ tane template parametresi bulundurabilen template parametresi tipidir.
```C++
template <typename ...Args>
// ...
```
Oyle bir template parametresi ki bu template parametresinden kod olusturma asamasinda asagidakilerden biri tanimlanmis gibi kod uretebilecektir:
```C++
template<typename P1>
// ...

template<typename P1, typename P2>
// ...

template<typename P1, typename P2, typename P3>
// ...
```

* Bir sinif sablonu ile yada fonksiyon sablonu ile kullanilabilir.
  ```C++
  template <typename ...Args> // ...Args => template type parameter pack
  class Myclass{
    // ...
  };
  
  template<typename ...Args>  // ...Args => template type parameter pack
  void func(Args ...params)   // Args... => pack expansion
  {
    // ...
  }
  ```
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  Myclass<int> x0;
  Myclass<int, int> x1;
  Myclass<int, long, double> x2;
  
  func(x);
  func(x, y);
  func(x, y, d);
  ```
  </details>
  <!--  -->

> **Not**  
> Geleneksel olarak bir variadic template parameter ismi icin `Args`, `Ts` veya `Types` isimleri kullanilmaktadir.


* Template parametreleri ile bir arada kullanilabilir.
  ```C++
  template <typename T, typename ...Args>
  void func(T t, Args... params){
    // ....
  }
  ```
* Template parameter pack, parametre siralamasinda sonda olmak zorunda degildir.
  ```C++
  template <typename ...Args, typename T>
  void func(T t, Args... params){
    // ....
  }
  ```
  
* Template parameter pack, **type parameter** veya **non-type parameter** olabilir.
  ```C++
  template <int ...N>
  class Myclass{};
  ```
  ```C++
  Myclass<12> m1;
  Myclass<12, 24> m2;
  Myclass<12, 34, 13> m3;
  ```
  
* Template argumanlari explicit olarak belirtilebilmektedir.
  ```C++
  template <typename ...Args>
  void func(Args&... params)
  {
  }
  ```
  ```C++
  func<int, double, long>('A', 3.4f, 34);
  ```

## `sizeof...` operatoru
*variadic sizeof operatoru*

Operandinda belirtilen template parameter pack icinde bulunan parametre adetini belirten bir operatordur.

```C++
template<typename ...Args>
void func(Args... params)
{
    constexpr auto n1 = sizeof...(Args);
    constexpr auto n2 = sizeof...(params);
}
```
* Pack expansion ve `sizeof...` operatoru:
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename ...Args>
  class Var {
    //...
  };
  
  template <typename ...Types>
  class Myclass : public Var<Types...> {
  public:
    constexpr static size_t size = sizeof...(Types);
  };
  ```
  ```C++
  constexpr auto n = Myclass<int, double>::size;  // n = 2
  ```
  `Myclass<int, double>` icin pack expansion yapildiginda:
  ```C++
  class Myclass : Var<int, double> {}
  ```
  </details>
  <!--  -->
  

## Pack expansion
Template type parameter pack'in derleyici tarafindan acilmis halidir. Parametre paketindeki parametrelerin belirtilen **bir kaliba uygun olarak** virguller ile ayrilan listeye donusturulmesi olarak da ifade edilebilir.

```C++
template<typename ...Args> // ...Args => template parameter pack
void func(Args ...params)  // Args...=> pack expansion, params => function parameter pack
{
}
```
Yukaridaki variadic fonksiyon sablonu icin asagidaki fonksiyon cagrilari yapilmasi karsiliginda derleyicinin olusturacagi fonksiyonlarin imzalari asagidaki gibidir:
```C++
func();                   // void func()
func(1);                  // void func(int)
func(1, 2.3);             // void func(int, double)
func(1, 2.3, "alican");   // void func(int, double, const char*)
```

* Her bir parametre icin [template argument deduction](341_template_params_and_args.md#template-argument-deduction) yapilmaktadir.
* En fazla 1 adet template parameter pack bulunabilmektedir.
  <!-- ? Aciklama gerek ? -->
* Template parameter pack, bir declaratore sahipse *(orn: const, &,\*,&& vb.)*, **acilan tum parametrelere** uygulanmaktadir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename ...Args>
  void func1(Args& ...args);
  
  template <typename ...Args>
  void func2(const Args& ...args); 
  
  template <typename ...Args>
  void func3(Args&& ...args); 
  ```
  ```C++
  func1(123, 3.14); //  void func(int&, double&);
  func2(123, 3.14); //  void func(const int&, const double&);
  func3(123, 3.14); //  void func(int&&, double&&);
  ```
  </details>
  <!--  -->
  
* Pack expansion yapilan yerlerde `...` *(elipsis)* **ifadeden sonra** kullanilir. 
* Parametre paketini ne sekilde kullanilirsa pack expansion yapildiginda her bir parametreye uygulanmaktadir.
  ```C++
  template<typename ...Args>
  void func(Args... args)
  {                       // func(10, 20L, 1.2) icin pack expansion sonucu uretilen kodlar:
    ++args...;            // ++p1, ++p2, ++p3;
    std::tuple<Ts...> t;  // std::tuple<int,long,double> t;
    foo(args...);         // foo(p1, p2, p3);
    foo(&args...);        // foo(&p1, &p2, &p3);
    bar(args)...;         // bar(p1), bar(p2), bar(p3);
    baz(bar(args)...);    // baz(bar(p1), bar(p2), bar(p3));
  }
  ```

* Bir **cikarim yapilabildigi surece** variadic template parametre paketi template argumanlardan herhangi birinde kullanilabilmektedir. Dolayisiyla variadic parametre paketi **son parametre olmak zorunda degildir**. 
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  template <typaname A, typename B, typename... Args>
  void func(A arg1, B arg2, Args ...pack)
  {
    std::tuple<A, B, Args...> t1; // std::tuple<A, B, E1, E2, E3>
    std::tuple<A, Args..., B> t2; // std::tuple<A, E1, E2, E3, B>
    std::tuple<Args..., A, B> t3; // std::tuple<E1, E2, E3, A, B>
    
    cout << "t1 = " << typeid(t1).name() << '\n';
    cout << "t2 = " << typeid(t2).name() << '\n';
    cout << "t3 = " << typeid(t3).name() << '\n';
  }
  ```
  ```C++
  func(1, 4.5, 'C', 4.5f, 4L);  // A = int, B = double, Args = char,float,long
                                // func cagrisi icin t1, t2 ve t3:
                                // t1 = std::tuple<int, double, char, float, long>
                                // t2 = std::tuple<int, char, float, long, double>
                                // t3 = std::tuple<char, float, long, int, double>
  ```
</details>
<!--  -->


### Pack expansion ile parametreler nasil kullanilir
-----------------------------------------------------
Parametre paketindeki parametreleri nasil dolasabiliriz? Ornegin, sembolik olarak asagidaki gibi bir kod olusturulmak isteniyor:
```C++
template <typename ...Args>
void print(const Args& ... args) 
{
  /*
  std::cout << p1 << ' ';
  std::cout << p2 << ' ';
  std::cout << p3 << ' ';
  */
}
```
En az 4 farkli teknik bulunmaktadir: 
1. Compile-time recursivity  
2. Virguller ile ayrilan listeye donusturup, tek fonksiyon ile yapmak
3. `if constexpr` [C++17]
4. Fold expression syntax araci [C++11]

#### Compile-time recursive pack expansion
-----------------------------------------------------
Derleyici verilen her parametre icin bir fonksiyon olusturarak template parameter pack icin eksiltme uygulamasina dayanmaktadir. Her pack expansion yapildiginda bir arguman eksilerek print cagrisi tekrarlaniyor.

**Ornek 1**
Asagidaki ornekte, variadic olarak yazilmis `(2)` fonksiyonuna yapilan ilk cagrida, derleyici *(compile-time'da)* ilk parametreyi bir `T` parametresine cikarim yapmakta, kalan parametreleri ise `Ts` template parameter pack icinde almaktadir. Gelen ilk parametre `T` ile `(1)` cagrisi yapilmakta, kalanlar icin ayni islem tek parametre kalana kadar uygulanmaktadir.
```C++
template <typename T>
void print(const T& val){                       // (1)
    cout << val << '\n';
}

template<typename T, typename ...Ts>
void print(const T& arg1, const Ts& ...args)    // (2)
{
    print(arg1);
    print(args...);
    
    // standart degil
    std::cout << __FUNCSIG__ << '\n';           // msvc
    std::cout << __PRETTY_FUNCTION__ << '\n';   // gcc, clang
}
```
`print(10, 23.5, 9L, "necati");` cagrisi icin sirasiyla print cagrilari ve cagrilan fonksiyon imzalari su sekilde:
```C++
// void print(const T&, const Ts& ...) [with T = int; Ts = {double, long int, char [7]}]
print(10, 23.5, 9L, "necati");

// void print(const T&) [with T = int]
print(10);

// void print(const T&, const Ts& ...) [with T = double; Ts = {long int, char [7]}]
print(23.5, 9L, "necati");

// void print(const T&) [with T = double]
print(23.5);

// void print(const T&, const Ts& ...) [with T = long int; Ts = {char [7]}]
print(9L, "necati");

// void print(const T&) [with T = long int]
print(9L);

// void print(const T&) [with T = char [7]]
print("necati");
```
[Ornek](res/src/pack_expansion01.cpp)
> **NOT** Son kalan parametre variadic template'i kullanmadigi icin recursive yapi sonlandirabildi.


**Ornek 2**
```C++
template<typename T>
constexpr T summer(T v) {
    return v;
}

template<typename T, typename ...TArgs>
constexpr T summer(const T& first, const Args& ... args) 
{
    return first + summer(args...);
}
```
Yukaridaki ornekten farkli olarak `summer(10, 20, 30, 40)` ifadesi icin sonuc compile-time'da hesaplandi.

#### [Virgul operatoru](050_basics.md#comma--operatoru) ile parameter pack expansion
-----------------------------------------------------
Virgul operatorunun **urettigi degerin sag operand degeri olmasindan faydalanilarak** pack expansion sonucunda ayni turden nesnelerden olusan bir `initializer_list` olusturulmasindan faydalanilir.

```C++
template <typename ...TArgs>
void print(TArgs ...args)
{
    (void) std::initializer_list<int>{ (std::cout << args << ' ', 0)... };
}
```

#### [if-constexpr](#TODO) kullanilarak
-----------------------------------------------------

```C++
template <typename ...TArgs>
void print(TArgs ...args)
{
    if constexpr(sizeof...(args) == 1) {
        std::cout << args << ' ';
    }
    else{
        std::initializer_list<int>{ (print(args), 0)... };
    }
}
``` 

### Pack expansion ile ilgili bazi idiomlar
* Template argumanlarinin, `A` sinifina kalitim yolu ile eklenmesi:
  ```C++
  template <typename ...Types>
  class A : public Types ... {
  public:
      A() : Types{0}...
      {
          
      }
  };
  ```
  `A<X, Y, Z> ax` bildirimi yapilmasi durumunda pack expansion sonucu derleyici asagidaki gibi bir kod uretir:
  ```C++
  class A : public X, public Y, public Z {
  public:
      A() : X{0}, Y{0}, Z{0}
  };
  ```

* `using` bildirimi ile kullanimi:
  ```C++
  struct A {
    void func(int);
  };
  
  struct B {
    void func(double);
  };
  
  struct C {
    void func(long);
  };
  
  template<typename ...Args>
  struct D : public Args... 
  {
    using Args::func...;
  };
  ```
  `D<A, B, C>` icin pack expansion sonucu:
  ```C++
  struct D : public A, public B, public C {
    using A::func, B::func, C::func;
  };
  ```
  Dolayisiyla `func` fonksiyonlari arasinda `using` bildirimi ile olusturulan overload etkisi asagidaki gibidir:
  ```C++
  D<int, double, long> x;
  x.func(23);       // calls A::func
  x.func(12.23);    // calss B::func
  x.func(1223L);    // calss C::func
  ```
  
  > **Hatirlatma**  
  > Modern C++'dan once `using` bildirimi liste olarak yapilamamaktaydi.

* Perfect forwarding ve parameter pack expansion kullanimi:
  ```C++
  template <typename ...Ts>
  void func(Ts&& ...args) 
  {
    foo(std::forward<Ts>(args)...); // elipsisin nerede olduguna dikkat edin
  }
  ```
  `func(10, 20L, 1.2)` cagrisi icin pack expansion sonucu:
  ```C++
  void func(int p1, long p2, double p3) 
  {
    foo(std::forward<int>(p1), std::forward<long>(p2), std::forward<double>(p3));
  }
  ```
  
* type variadic parameter pack ile non-type variadic parameter pack kullanimi:
  ```C++
  template<typename... Types, int... N>
  void func(Types(&...args)[N])
  {
    // ...
  }
  ```
  ```C++
  int a[5]{};
  int b[10]{};
  int c[20]{};
  double d[5]{};
  
  func(a, b, c, d);
  ```
  `func(a, b, c, d)` cagrisi icin pack expansion:
  ```C++
  void func(int(&p1)[5], int(&p2)[10], int(&p3)[20], double(&p4)[5])
  {
    // ...
  }
  ```
* Parameter pack non-type parametre paketi de olabilir.
  ```C++
  template<size_t ...n>
  struct A { 
    A() {
        std::cout << typeid(A).name() << '\n';
    }
  };
  
  template<size_t ...n>
  void func()
  {
    A<n...> ax;
  }
  
  func<1,3,5,7>();
  ```
