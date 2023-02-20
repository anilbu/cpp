## `const` anahtar sozcugu

```C++
const int x = 10;
```

* `const` anahatar sozcugu ile tanimlanan bir degisken **immutable**dir. 
* `const` anahtar sozcugu ile bildirilen degiskenler default initialize edilemiyorlar, ilklendirilmeleri zorunludur. Ilklendirme ifadesinin `constexpr` olmasi zorunlu degildir.
  ```C++
  int foo();
  const int x = foo();
  ```
* `const` bir degisken ilklendirmesini bir `constexpr` bir ifadeden almis ise kendisinin olusturdugu ifade bir `constexpr`dir, aksi halde constexpr degildir.
  ```C++
  const int x = 10;
  const int y = 20;
  const int z = 30;
  int a[x + y + z];     // x, y, z ve x+y+z ifadeleri birer constexpr'dir
  ```
  ```C++
  int foo(void);
  
  const int w = foo();
  int a[w];     // syntax error: w ifadesi bir constexpr degildir.
  ```

* `const` ayri bir tur olusturur.
  ```C++
  const int x = 10;
  decltype(x) y;              // y = const int
  ```

> **DIKKAT!**
> Derleyici `constexpr` veya `const` degiskenler icin bellekte yer ayirmak zorunda degildir. Ancak degiskenin **adresine erisim** varsa yer ayirmak zorunda kalir.

## typedef bildirimleri

> **Not**
> Pratik bilgi: Bir tur es ismi tanimi icin:
> 1. Hangi ture es isim verilecekse o turden bir degisken tanimla
> 2. Basina `typedef` koy.
> 3. Degiskenin ismini tur es ismi olarak degisitir.


## `comma operator`

```C++
expr1, expr2
```
1. comma operatoru bir sequence point olusturur.  
   expr1 her zaman expr2'den once evaluate edilir ve tum side-effectler gerceklesir.
2. Urettigi deger sag operandin degeridir.  
   Yukaridaki ifade expr2 degerini uretir.

```C++
int a[] = { (exp1, 0), (exp2, 0), (exp3, 0) };                  // a = {0, 0, 0};
std::initializer_list<int> { (exp1, 0), (exp2, 0), (exp3, 0) }; // {0, 0, 0}
```