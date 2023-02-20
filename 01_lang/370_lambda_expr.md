# Lambda Expressions - 1
*lambda functions*

<!-- 32. dersin sonunda basliyor -->
Bir lambda ifadesi; derleyicinin bir sinif (closure-type) kodu yazarak ifadenin kendisini bu sinif turunden gecici nesneye (closure-object) donusturmesini saglamakta, dolayli olarak local fonksiyon olusturulabilmesini saglamakta olan bir aractir. Lambda ifadeleri Modern C++11 ile dile eklenmistir.

```C++
[capture-clause] (params) specifiers
{ 
    // body
}
```
* `[]` : **lambda introducer** Bir lambda ifadesi bu paranteze sahip olmalidir.
* `()` : Derleyicinin yazacagi sinifin fonksiyon cagri operator fonksiyonun parametrelerini belirtir. Opsiyoneldir.

* Uye fonksiyon `mutable`, `noexcept`, `constexpr` ve `trailing return type` specifierlarindan
  biri yada birden fazlasi ile birlikte nitelenebilir.
  
  * Uye fonksiyonun `non-const` olmasi icin `mutable` keywordu kullanilir.  
    Default olarak uye fonksiyon, bir **const uye fonksiyon**dur.
    ```C++
    [](int x, int y) mutable {}
    ```

  * Uye fonksiyonun bir exception throw etmeme garantisini verdigini belirtmek icin `noexcept` specifier kullanilir.  
    Default olarak uye fonksiyon **noexcept garantisi vermez**.
    ```C++
    [](int x, int y) noexcept {}
    ```

  * Uye fonksiyonun bir `constexpr` oldugunu belirtir.  
    Default olarak constexpr olmasini **engelleyecek bir durum olmadigi surece constexpr** kabul edilir.
    **constexpr** specifieri, fonksiyon kodunun constexpr olmadigi durumda **syntax hatasi uretmek icin** kullanilir.
    ```C++
    [](int x, int y) constexpr {}
    ```
  * Uye fonksiyonun return type'ini belirtmek icin `trailing return type` specifier kullanilir.  
    Default olarak **return ifadesinden cikarim yapilir**.
    ```C++
    [](int x, int y) -> int {}
    ```

* Eger parametresi olmayan bir fonksiyon herhangi bir specifier ile nitelenmemis ise `()` dusurulebilir.
  ```C++
  []{ std::cout << "necati"; };
  ```

* Lambda ifadesi karsiligi olusturulan siniflar lambda ifadesi tanimi birebir ayni olsa dahi **farkli turler**dendir.  
  ```C++
  #include <type_traits> 
  
  auto f1 = [](int x) { return x * x; };
  auto f2 = [](int x) { return x * x; };
  
  constexpr auto b = is_same_v<decltype(f1), decltype(f2)>;   // b = false
  ```
  ```C++
  auto f1 = [](int x) { return x * x; };
  auto f2 = f1;
  constexpr auto b = is_same_v<decltype(f1), decltype(f2)>;   // b = true
  ```

* C++20 oncesinde lambda ifadelerinin olusturdugu siniflarin (closure types) atama operator fonksiyonlari ve default ctor'lari delete ediliyordu.  
  Ancak C++20 ile bu kural degistirildi, artik [stateless lambda](#statelessstateful-lambda) ifadelerinin default ctorlari ve atama operator fonksiyonlari delete edilmiyor.
  ```C++
  auto f1 = [](int x) { return x * x; };
    
  decltype(f1) f3;  // C++17'de gecersiz: default ctor deleted
                    // C++20'de gecerli
                    
  f2 = f1;          // C++17'de gecersiz: operator= deleted
                    // C++20'de gecerli
                    
  constexpr auto b = is_same_v<decltype(f1), decltype(f2)>;   // b = true
  ```

* Lambda ifadeleri icinde, fonksiyonun ana blogunda **gorunur durumdaki static omurlu degiskenler** dogrudan kullanabilirdir.
  ```C++
  static int ival = 56;
  auto f = [](int x) { 
    std::cout << x + ival << '\n';  // std::cout ve ival direkt olarak kullanilabiliyor.
  };
  
  f(34);
  ```
  
* Local degiskenler, lambda icerisinde dogrudan kullanilamazlar, capture edilmelilerdir.

## Lambda Capture
Capture list, lambda body'sinde disaridan erisilen degiskenleri ve capture yontemini tanimlar. [Ornek](res/src/lambda01.cpp)

`[=]` gorunur olan tum degiskenler **capture by copy** yapilir.
`[&]` gorunur olan tum degiskenler **capture by reference** yapilir.

<!--  -->

* capture edilecek nesneler lambda olusturulan yerde gorunur olmalidir.
* static omurlu nesneler (global, static) capture edilemezler.
  *capture edilen nesne mi yoksa global/static orjinal nesne mi kullanilacak belli degil. Ayrica lambda bodysi icinde zaten gorunur durumdalar.*

### Stateless/Stateful Lambda
Eger bir lambda ifadesi herhangi bir degiskeni capture etmiyorsa **stateless lambda**, ediyorsa **stateful lambda** ifadesidir.

* ```C++
  int x = 12;
  auto f1 = [](int a) { return a * a; };  // stateless
  auto f2 = [x](int a) { return a * x; }; // stateful
  
  decltype(f1) _f1; // gecerli [C++20]
  decltype(f2) _f2; // syntax error: f2 stateless degil
  ```

* Stateless lambda ifadeleri, derleyicinin urettigi kodda fonksiyon pointer turune ortulu donusum yapacak donusum operator fonksiyonuna sahiptir.
  ```C++
  inf foo(int);
  
  using f_ptr = int(*)(int);
  struct Myclass {
    int operator()(int x);
    operator f_ptr() const;
  };
  
  void f() {
    int a = 10;
    int (*fp)(int);
    fp = foo;
    
    auto f_stateless = [](int x) { return x * x; };
    fp = f_stateless; // gecerli
    
    auto f_stateful = [a](int x) { return x * a; };
    fp = f_stateful;  // syntax error
  }
  ```

## Closure type
```C++
int a = 10;
int b = 20;

auto f = [a, &b](int x){
    return a * x + b;
}

f(30);
```
Yukaridaki lambda ifadesine karsi derleyicinin urettigi kod (closure type) asagidaki gibidir: *([cppinsights.io](https://cppinsights.io/))*
```C++
class comp_gnt_xyazs1234_ { 
public:
    comp_gnt_xyazs1234_(int& _a, int& _b) : a{_a}, b{_b} {}
    
    inline int operator(int x, int y) const {
        return (a * x) + b;
    }
private:
    int a;
    int& b;
};
```
```C++
int a = 10;
int b = 20;
comp_gnt_xyazs1234_ f = comp_gnt_xyazs1234_{a, b};
f.operator(30);
```

**Ornekler**
* capture ornekleri
  ```C++
  int g = 10;
  
  void func() 
  {
    string name { "coskun" };
    int x = 10;
    double d = 3.14;
    
    auto f1 = [=](){};      // tumu capture by copy
    auto f2 = [&](){};      // tumu capture by ref
    auto f3 = [&, x](){};   // x haric hepsi referans ile, x copy ile capture et
    auto f4 = [=, &x](){};  // x haric hepsi copy ile, x capture by ref
    auto f5 = [g](){};      // syntax error 
  }
  ```
* `operator()` fonksiyonu `const` olsa dahi ref degismedigi icin (ref edilen degisken, degiskenin degeri degil) mutable olmasa da capture by reference yapilan degisken degistirilebilir.

  Asagidaki ifade bir syntax error uretir, cunku lambda karsiligi uretilen `operator()` fonksiyonu `const` uye fonksiyondur:
  ```C++
  int a = 10;
  auto f1 = [a](int x) {
      a *= x;     // syntax error
  };
  ```
  ```C++
  auto f2 = [a](int x) mutable {
      a *= x;     // gecerli
  };
  
  auto f3 = [&a](int x) {
      a *= x;     // gecerli
  };
  ```
  
## Trailing return type
Bazen lambda ifadelerinde birden fazla farkli turde return statement olabiliyor.
```C++
auto f = [](int x) {    // syntax error: birden fazla turde cikarim yapilamiyor.
  if(1) {
    return x * 1.3;
  }
  
  return x + 2;
};
```
Derleyicinin return statementdan cikarim yapmaya calismasi yerine return tipi **trailing return type** ile belirtilebilir.
```C++
auto f = [](int x) -> double {
  if(1) {
    return x * 1.3;
  }
  
  return x + 2;
};
```

## Generalized Lambda Expression / Overload Resolution

[C++14] Bir lambda ifadesi olustururken, fonksiyonun `operator()` fonksiyonunu template olarak olusturmasini saglanabilir.

```C++
auto f = [](auto x) { return x + x; };
```
Yukaridaki lambda ifadesi icin asagidaki gibi bir closure type uretilmektedir:
```C++
class xyz { 
public:
  template<typename T>
  void operator()(T x)
  {
    return x + x;
  }
};
```

Bazen kullanilan sinif turleri oldukca uzun olabiliyor...
```C++
vector<list<shared_ptr<string>>::iterator> vec;

sort(vec.begin(), vec.end(), 
[](const list<shared_ptr<string>>::iterator& r1, const list<shared_ptr<string>>::iterator& r2) {
  
});
// yerine 
sort(vec.begin(), vec.end(), 
[](const auto& r1, const auto& r2) {
  
});
```

Bazi yerlerde cikarim yapmak mumkun degil:
```C++
int func(int);
double func(double);
long func(long);

vector<int> ivec;

for_each(ivec.begin(), ivec.end(), &func);  // syntax error: Hangi func?

// 1. tur donusum operatoru kullanmak
for_each(ivec.begin(), ivec.end(), (int(*)(int)) &func);

// 2. overload resolution idiom
for_each(ivec.begin(), ivec.end(), [](auto x){ 
  func(x);
}]);
```

## Kullanimi ve idiomatik ifadeler

* Bir lambda ifadesi isimlendirilerek:
  * daha sonra cagrilabilir.
  * birden fazla noktada cagrilabilir.
  * const olarak tanimlanabilir.
  ```C++
  auto f1 = [](int x) { return x * x; };
  auto f2( [](int x) { return x * x; } );
  auto f3{ [](int x) { return x * x; } };
  
  const auto cf = [](int x) { return x * x; };  // cf tekrardan atanamaz
  
  cout << f1(12) << '\n';
  ```

function pointer  
functor/function object

* Bir lambda ifadesini bir fonksiyon template'ine arguman olarak gondermek
  ```C++
  vector<int> ivec_src {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  vector<int> ivec_dst(ivec_src.size());
  
  copy_if(ivec_src.begin(), ivec_src.end(), ivec_dst.begin(), [](int x) {
    return x % 2 == 0;
  });
  ```

* Lambda ifadeleri ile olusturulan closure objects bir container'da tutulabilir.  
  ```C++
  // ???
  ```
  
* Bir fonksiyon bir lambda ifadesi ile olusturulan nesneyi return edebilir.
  ```C++
  auto func(int x) {
    // codes...
    return [x](int a, int b) { return x * (a + b); };
  }
  
  auto f = func(5);
  f(10, 20);
  ```
  
* Bir lambda ifadesi baska bir lambda ifadesi return edebilir.
  ```C++
  int x = 10;
  auto f = [x](int a) { 
    return [a](int i) {
        return i * x + a;
    };
  };
  
  f(20)(30);
  ```

  
### (IIFE) Immediately Invoked Function Expression
Bir lambda ifadesinin bulundugu yerde fonksiyonu cagirilmasidir.

*Neden IIFE kullanilir?*  

`const` bir nesneye ilk deger verilirken, kompleks bir hesaplamanin yapilarak ilklendirmenin yapilabilmesini saglamaktir.
  
```C++
int x = 13;
int y = 34;

const double dval = [](int a, int b){ 
  int x = a * a + b * b;
  int y = a * a * a - 1;
  int z = b * b * b - 3;
  return 0.1923 * (x + y + z);
}(x, y);
```
```C++
class MyClass { 
public:
  MyClass() : mx { [](int a, int b){ 
                  int x = a * a + b * b;
                  int y = a * a * a - 1;
                  int z = b * b * b - 3;
                  return 0.1923 * (x + y + z);
              }(10, 20) } 
{
}
private:
  double mx;
};
```

### Positive Lambda Idiom

Eger isaret operatoru `+`'yi bir ifade ile kullanilir ise bu ifadenin bir adres, tamsayi yada gercek sayi turunden olmasi gerekir.

Stateless lambda ifadelerinde ise bu durumda fonksiyon pointeri turune donusum yapilir.

```C++
auto f1 = [](int a) { return a * a; };
cout << typeid(f1).name() << '\n';  // class int __cdecl main(void)::2::<lambda_1>

auto f2 = +[](int a) { return a * a; };
cout << typeid(f2).name() << '\n';  // int(*)(int)
```
```C++
template<typename T>
void func(T t) 
{
  ///
}

func( [](int x){ return x + 5; });    // T = closure type
func(+[](int x){ return x + 5; });    // T = void(*)(int)
```


