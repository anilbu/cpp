# Type Deduction
Compile-time derleyici tarafindan koda bakilarak tur cikarimi yapilmasidir. Bu araclar reflection'dan farkli olarak runtime'da degil, compile-time'da gerceklesmektedir.

Tur cikarimi icin kullanilan araclar:
* `auto`
* `decltype`
* `decltype(auto)`
* `template`

## `auto` type deduction
Bildirilen bir degiskenin ilk degerini veren ifadenin turunden cikarim yaparak belirleyen compile-time'da calisan bir aractir.

```C++
auto x = expr;
```
Tur cikarimi `auto` anahtar sozcugu karsiligi yapilmaktadir, bildirilen degiskenin turu icin degil.
`T` turunden bir `expr` ifadesi icin:
```C++
auto x = expr;       // auto = T, x = T
const auto x = expr; // auto = T, x = const T
auto* x = expr;      // auto = T, x = T*
```
```C++
int i = 0;
auto x = &i;         // auto = int*, x = int*
auto* x = &i;        // auto = int,  x = int*

int* ptr = &i;
auto p1 = &ptr;      // auto = int**, x = int**
auto* p2 = &ptr;     // auto = int*,  x = int**
auto** p3 = &ptr;    // auto = int,   x = int**
```

**Ornekler**
```C++
int i = 45;
char c = 'a';

auto x = i;       // auto = int
auto x = c;       // auto = char
auto x = +c;      // auto = int        +operatoru integral promotiona neden olur
auto x = 10 > 5;  // auto = bool
auto x = i * 1.2; // auto = double
```

* `auto` ile bildirilen bir degiskene ilk deger vermek mecburidir.
* `auto` ile bildirilen bir degiskene ilk deger veren nesnenin **const** olmasi durumunda `const` duser.
  ```C++
  const int ci = 6;
  auto x = ci;          // auto = int, x = int (const int degil)
  ```
* `auto` ile bildirilen bir degiskene ilk deger veren ifade **reference degisken**in olusturdugu ifade ise ref duser.
  ```C++
  int i = 10;
  int& r = i;
  auto x = r;           // auto = int, x = int (int& degil)
  ```
  const ref olmasi durumunda hem const hem de ref duser.
  ```C++
  const int& cr = i;
  auto x = cr;          // auto = int, x = int (const int& degil)
  ```
* `auto` ile bildirilen bir degiskene ilk deger veren ifade bir **adres** turunden ise cikarim yapilirken top-level const duser, ancak low-level const korunur. *Aksi halde sentaks hatasi olusurdu.*
  ```C++
  int* const ptr{};
  auto x = ptr;         // auto = int*, x = int*
  ```
  ```C++
  const int ci = 10;
  auto x = &ci;         // auto = const int*, x = const int*
  ```
* `auto` ile bildirilen bir degiskene ilk deger veren ifade `string literal` ise cikarim `const char*` turune yapilir.
  ```C++
  auto p = "murat";     // auto = const char*
  ```
* `auto` ile bildirilen bir degiskene ilk deger veren ifade bir **dizi** turunden ise array-decay uygulandiktan sonra tur cikarimi yapilir.
  ```C++
  int a[5] = {};
  auto x = a;           // auto = int*, x = int*
  ```
  `&a` ifadesinde array decay uygulanmadigi icin, `int[5]` turunden bir nesnenin adresine cikarim yapilir.
  ```C++
  auto x = &a;          // auto = int(*)[5], x = int(*)[5]
  ```
  `const int[5]` turunden bir array `const int*`'a decay olmasi nedeniyle cikarim `const int*`a yapilir.
  ```C++
  const int ca[5] = {};
  auto x = ca;          // auto = const int*
  ```
* `auto` ile bildirilen bir degiskene ilk deger veren ifade bir **function** turunden ise function-decay uygulandiktan sonra tur cikarimi yapilir.
  ```C++
  int foo(int);         // foo = int(int)
  auto fp = foo;        // auto = int(*)(int)
  ```


> **DIKKAT!**  
> C++11'de `auto` eklenmesinden sonra iki kere kural degisikligi yapilmistir.
> `= {}` ile ile initialize edilen bir auto bildiriminde cikarim `std::initializer_list`dir.
> `{}` ile initialize edilen bir auto bildiriminde unified initialization kullaniliyor, daha onceden bu da `std::initializer_list` idi.
> ```C++
> auto x = {1, 2, 3, 4, 5}; // auto = std::initializer_list<int>
> auto x(0);                // auto = int
> auto x{ 0 };              // auto = int
> ```

> **DIKKAT!**  
> `auto` anahtar sozcugu farkli baglamlarda farkli anlamlar ifade edebilmektedir.

[bknz: AAA (almost always auto)](999_kavramlar.md#aaa-almost-always-auto)


### `auto&` tur cikarim kurallari
* `auto&` declaratoru ile bildirilen bir degiskene cikarim yapilirken constluk dusmez. Aksi halde const olan bir nesneye non-const bir ref olusurdu.
  ```C++
  int i = 10;
  auto& r = i;          // auto = int, r = int&
  ```
  
  ```C++
  const int ci = 10;
  auto& r = ci;         // auto = const int, r = const int&
  ```
* `auto&` declaratoru ile bildirilen bir degiskene ilk deger veren ifade bir `dizi` turunden ise cikarim yapilirken array-decay uygulanmaz.
  ```C++
  int a[3] = {};
  auto& x = a;          // auto = int[3], x = int(&)[3]
  ```
  `string literal` icin de benzer durum gecerlidir.
  ```C++
  auto& x = "hello";    // auto = const char[6], x = const char[6]
  ```
* `auto&` declaratoru ile bildirilen bir degiskene ilk deger veren ifade bir `function` turunden ise cikarim yapilirken function-decay uygulanmaz.
  ```C++
  int func(int);
  auto& x = func;       // auto = int(int), x = int(&)(int)
  ```
  [Soru](sorular/soru07.cpp)
  
### `auto&&` tur cikarim kurallari
`auto&&` ile bildirilen bir degiskene ilk deger veren ifadenin deger kategorisine bagli olarak cikarim yapilir. 

* `auto&&` ile bildirilen bir degiskene ilk deger veren ifadenin deger kategorisi **rvalue expr** ise `auto` karsiligi yapilan cikarim `T` ve olusan tur `T&&`'dir.
  ```C++
  auto&& x = 20;        // auto = int, x = int&&
  ```
* `auto&&` ile bildirilen bir degiskene ilk deger veren ifadenin deger kategorisi **lvalue expr** ise `auto` karsiligi yapilan cikarim `T&` ve olusan tur [reference collapsing](100_ref_semantics.md#reference-collapsing) sonucu `T&`dir.
  ```C++
  int i;
  auto&& x = i;         // auto = int&, x = int&
  ```

## `decltype` type deduction
`decltype` operatorunun operandi olan ifadenin tur bilgisi cikarilarak, bir tur belirtimini saglayan bir aractir. `decltype` ile uretilen tur, tur kullanilabilecek herhangi bir yerde kullanilabilirdir.

```C++
decltype(operand)
```

* `decltype` ile degisken uretmek zorunlu degildir.
* `()` operatorun sentaksinin bir bileseni olmasi nedeniyle kullanimi zorunludur.
* `decltype` operatorunun operandi **unevaluated context**tir.

<!--  -->

Decltype operandin turune gore farkli kural setlerine sahiptir.

### identifier icin cikarim kurallari
```C++
decltype(<identifier>)
```
decltype karsiligi identifier (ismin) turu ile ayni olacak bicimde cikarim yapilacaktir.

[Ornekler](res/src/type_deduction_decltype02.cpp)



### expression icin cikarim kurallari
```C++
decltype(expr)
```
Hangi turun elde edilecegi operand olan `expr` ifadesinin primary value categorysine baglidir.

`expr`nin turu `T` oldugu varsayilir ise:

* `expr` ifadesi bir **prvalue** ifadesi ise elde edilecek tur `T`'dir;
* `expr` ifadesi bir **lvalue** ifadesi ise elde edilecek tur `T&`'dir;
* `expr` ifadesi bir **xvalue** ifadesi ise elde edilecek tur `T&&`'dir;

[Ornekler](res/src/type_deduction_decltype03.cpp)




<!--  -->

> **DIKKAT!**  
> `x` bir isim, `(x)` ise bir expressiondir.
> ```C++
> decltype(x)      // int, isim kurallarina gore
> decltype((x))    // int&, expression kurallarina gore
> ```