# Constant Expressions

## `constexpr` anahtar sozcugu

Modern C++ ile dile eklenmistir. 
Ifadenin degeri derleyici tarafindan compile-time'da biliyor ise constant expression'dir.

* Dizi boyutu gosteren ifadeler (variable len arr haric)
* Global degiskenleri initialize eden degerler
* switch icinde bulunan case ifadeleri
* bitfield member

> :warning: 
> `const` ve `constexpr` farkli anahtar sozcuklerdir ve benzer noktalari olmasina ragmen farkli islevleri vardir. [[bknz: const anahtar sozcugu](050_basics.md#const-anahtar-sozcugu)]


```C++
constexpr int x = 10;
```

* `constexpr` ile tanimlanan degiskenlere constexpr ifade ile ilk deger verilmesi zorunludur.
* `constexpr` ile tanimlanan degiskenler bir baska sabit ifadesinin bileseni olarak da kullanilabilir.
* `constexpr` ile tanimlanan degiskenler implicit olarak `const` turdedirler.
  ```C++
  constexpr int x = 10;     // x = const int
  ```
* `constexpr` ile tanimlanan pointerlar top-level `const` turdedirler.
  ```C++
  constexpr int* p = nullptr;            // p = int* const
  constexpr const int* p = nullptr;      // p = const int* const
  ```
* `constexpr` tanimlanan diziler de olabilir.

[Ornek](res/src/constexpr01.cpp)


> :warning: 
> Derleyici `constexpr` veya `const` degiskenler icin bellekte yer ayirmak zorunda degildir. Ancak degiskenin **adresine erisim** varsa yer ayirmak zorunda kalir.

## `constexpr` functions
Belirli kosullar saglandiginda geri donus degeri compile-time'da uretilen fonksiyonlardir.

```C++
constexpr int func(int a, int b)
{
    return a * b - 3;
}
```

Bir fonksiyonun constexpr function olabilmesi icin su sartlari sagliyor olmasi gerekmektedir.
* Geri donus turu `void` fonksiyonlar constexpr olamazlar.
* static local variable kullanilamaz.
* `virtual` bir member function olamaz.
* Geri donus degeri turu, her bir parametre turu ve local degiskenlerin turu **literal type** olmasi zorunludur.

[Ornek](res/src/constexpr02.cpp)

<!--  -->

> :triangular_flag_on_post: 
> `constexpr` fonksiyonlar, **constexpr olmayan** argumanlar alabilirler. Ancak, `constexpr` fonksiyonlarin **compile-time'da hesaplanabilmesi icin** argumanlarinin tamami `constexpr` olmalidir. Aksi halde, normal fonksiyon gibi cagrilar gerceklesir.
> [Ornek](res/src/constexpr03.cpp)