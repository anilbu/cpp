## Function Templates

```C++
template <typename T>
T func(T x)
{
    T y{};
    T arr[10]{};
    return y;
}
```

* Template parametresine karsilik gelen tur ile fonksiyon parametresine karsilik gelen tur ayni olmak zorunda degildir.
  
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  `T`ye karsilik gelen tur `int` ise, `x` parametresi `int*` turundendir:
  ```C++
  template <typename T>
  void func(T* x)
  {
  }
  ```
  `T`ye karsilik gelen tur `int`, `U`ye karsilik gelen tur `double` ise, `fp` call parametresi `int (*)(double)` turundendir.
  ```C++
  template <typename T, typename U>
  void func(T (*fp)(U))
  {
  }
  ```
  </details>
  <!--  -->
  
* Sinifin bir uye fonksiyonu template function olabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    template <typename T>
    T foo(T x);
  };
  ```
  ```C++
  Myclass m;
  m.foo<int>(10);
  ```
  </details>
  <!--  -->
  

* Function template specializationlari, function overload olusturur. Non-template fonksiyonlar ile de overload edilebilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template<typename T>
  void func(T x);
  
  template<typename T>
  void func(T x, T y);
  
  void func(int);
  ```
  </details>
  <!--  -->
  
* Fonksiyon sablonlari `delete` edilerek bildirilebilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  void func() = delete;
  ```
  </details>
  <!--  -->
  
* Fonksiyon sablolari icin `inline` anahtar sozcugunu kullanilmasa dahi **ODR'i ihlal etmemektedir**.
  *Normalde bir inline olmayan bir fonksiyonun baslik dosyasinda tanimlanmasi ODR'i ihlal eder.*


### abbreviated template syntax [C++20]

*Kisaltilmis sablon sentaksi*

Bir template fonksiyonunu yazmanin kisaltilmis yoludur. Template parametreleri, fonksiyon parametresinde `auto` anahtar sozcugu ile bildirilir *gibi*.

**Ornek**: Asagidaki iki fonksiyon aynidir.
```C++
template <typename T>
void func(T x) {
  T temp;
  ...
}
```
```C++
void func(auto x) {
  decltype(x) temp;
  ...
}
```

------------------------------
**normal return type**
```C++
int func() 
{
  return 0;
}
```

**trailing return type**
```C++
auto func() -> int
{
  return 0;
}
```

**auto return type**
Bildirilmis bir fonksiyon icin geri donus turunun derleyicinin return ifadesinden cikarim yaparak olusturmasidir. Templateler ile birlikte kullanilmak zorunda degildir.
```C++
auto func() // auto = int, func = int(void)
{
  return 10;
}
```

**decltype-auto return type**
```C++
decltype(auto) func()
{
  
}
```

[Soru: Parametresi olmayan, geri donus turu `int(*)(int)` olan bir fonksiyon olusturun.](sorular/soru15.cpp)

------------------------

```C++
template <typename T>
void func(T& x, T& y)
{
    T temp(x);
    x = y;
    y = temp;
}
```
Yukaridaki kod orneginde copy yapiliyor, ancak move semantik desteklenmemis. *Sadece move SMF'lari var ise calismayacaktir.* Ayrica olusturulan `temp` objesi icin *gecici de olsa* ekstra kaynak ayrildi.

```C++
template <typename T>
void func(T& x, T& y)
{
    T temp(std::move(x));
    x = std::move(y);
    y = std::move(temp);
}
```

-----------------------