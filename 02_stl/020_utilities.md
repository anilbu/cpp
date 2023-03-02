# Utility library
[cppref](https://en.cppreference.com/w/cpp/utility)  

## `std::allocator`

## `std::initializer_list`

```C++
template <typename T>
class initializer_list;
```
<p align="center">
    <img src="res/img/initializer_list.drawio.svg" width=""/><br/>
    <i>Sekil: std::initializer_list</i>
</p>

* `<initializer_list>` baslik dosyasinda tanimlidir.
* Ogeler icin derleyici `const` bir dizi olusturur, `initializer_list` bu diziye bir range olusturur. Bu ogelerin degistirilmesi **UB**dir.
* Elemanlar ayni turden olmak zorundadir.
* Elemanlarin constexpr olmasi zorunlu degildir.
  
[Ornek](res/src/initializer_list01.cpp)

## auto ile initializer_with kullanimi kurallari
C++11'den sonra initializer_list icin `auto` type deduction ile kurallar degisti.

* `initializer_list`e auto type deduction icin `=` kullanilmalidir.[C++17]
  ```C++
  auto x = {1, 4, 9, 2, 5};     // x = std::initializer_list<int>
  auto y { 10 };                // y = int
  auto y { 10, 20 };            // sentaks hatasi
  ```

* `auto` type deduction ile `template` type deduction mekanizmasinin kurallari **initializer_list istisna olmak uzere** tamamen aynidir.
  Bir fonksiyon sablonuna tur cikarimi yapilirken, initializer_list'e cikarim dogrudan yapilamaz.
  ```C++
  template<typename T>
  void func(T)
  {
  }
  
  auto x = {1, 2, 3, 4, 5}; // x = initialzier_list
  func({1, 2, 3, 4, 5});    // syntax error
  ```
* Sinifin initializer_list ctor'u soz konusu oldugu zaman `=` kullanimi zorunlu degildir. Oncelikli olarak `initializer_list` overloadu secilir.
  ```C++
  class Nec{ 
  public:
      Nec(int) {
          std::cout << "Nec(int)\n";
      }
      
      Nec(int, int) {
          std::cout << "Nec(int, int)\n";
      }
      
      Nec(std::initializer_list<int>) {
          std::cout << "Nec(std::initializer_list<int>)\n";
      }
  };
  
  Nec x1(12);         // Nec(int)
  Nec x2(12, 56);     // Nec(int, int)
  Nec x3{ 12 };       // Nec(std::initializer_list<int>)
  Nec x4{ 12, 56 };   // Nec(std::initializer_list<int>)
  ```
  
  
## `std::pair`

`<utility>`'de tanimlidir.

Mantiksal olarak birbiri ile iliskili iki turun bir arada tutulmasi icin kullanilir.

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

```C++
template<typename T, typename U>
struct pair{
  T first;
  U second;
};
```
</details>
<!--  -->

**Ornek**
```C++
std::pair<int, double> p{1, 0.5};
std::cout << "p.first = " << p.first << '\n';
std::cout << "p.second = " << p.second << '\n';
```

<details>
<summary><b>C dilinde</b> (Click to expand)</summary>

Template araci olmamasi nedeniyle fonksiyonel makro kullanilarak benzer bir yapi kurulabilir.
```C
#define cr_pr_type(t, u) struct Pair_##t##_##u { \
    t first;  \
    u second; \
}
```
```C
cr_pr_type(int, double) x;  // Pair_int_double x;
cr_pr_type(int, int) y;     // Pair_int_int y;
```
</details>
<!--  -->

* default initialize edilmesi halinde **value initialize** edilmektedir. Eger turlerden biri sinif turu ise, **default ctor** cagrilmaktadir.
* [C++17] CTAD ile initialize edilebilir
  ```C++
  pair x = {34, 3.14};
  ```
* Farkli turlerden pair nesneleri, eger `first` ve `second` memberlari karsilikli olarak atanabiliyor ise birbirlerine atanabilmektedir.
  ```C++
  pair<int, int> x {1, 2};
  pair<double, double> y {1.1, 2.2};
  pair<string, string> z { "" , "" }
  
  x = y;    // legal
  x = z;    // illegal
  ```

* `pair` sinif sablonunun `operator<<` ve `operator>>` overloadlari bulunmamaktadir.
 
**make_pair**
Basitlestirilmis olarak:
```C++
template <typename T, typename U>
std::pair<T, U> make_pair(const T& t, const U& u) {
  return std::pair<T, U>{t, u};
}
```
```C++
auto x = make_pair(12, Date{1,1,1923});
```



## `std::tuple`


## `std::bitset`


## Vocabulary Types
### `std::optional`


### `std::variant`


### `std::any`




