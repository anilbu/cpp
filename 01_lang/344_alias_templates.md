## Alias template

Bir tures ismi bildiriminde template parametresi kullanilarak tanim yapilabilmesini saglayan bir aractir.

```C++
template <typename T>
using ipair = std::pair<T, T>;
```
```C++
ipair<int> x;  // x = std::pair<int, int>
```

> **Tur-es isimleri hatirlatma**
> ```C++
> using Word = int;
> using FCMP = int (*)(const char*, const char*);
> using inta10 = int[10];
> using CIPTR = const int*;
> ```
> * Pointer tur-es isimlerinde, tur-es ismi `const` ile bildirilmis ise **top-level const**dur.
> * `typedef` bildirimi ile bir template tur-es ismi bildirimi yapmak mumkun degildi, ancak `using` bildirimi ile yapilabilmektedir.
> 

**Ornekler**
* Template argumanlarindan bazilarinin her zaman ayni tur olarak kullanilmasi:
  ```C++
  template <typename T>
  using s_pair = std::pair<std::string, T>;
  ```
  ```C++
  s_pair<int>         // std::pair<string, int>
  s_pair<double>      // std::pair<string, double>
  ```

  
* Template argumaninin birden fazla yerde ayni bicimde kullanimini kolaylastirmak:
  ```C++
  template<typename T>
  using greater_set = std::set<T, greater<T>>;
  ```
  ```C++
  set<int, greater<int>> iset;  // yerine
  greater_set<int> igset;
  ```

* 
  ```C++
  template<typename T>
  using ptr = T*;
  
  ptr<int> p;                 // int*
  ```

* 
  ```C++
  template<typename T, int n>
  using ar = T[n];
  
  ar<int, 20> x, y, z;         // hepsi int ar[20]
  ```

* Template argumanlarinda kullanilan uzun tur isimlerinin kisaltilabilmesi:
  ```C++
  template<typename T>
  using epvec = std::vector<std::pair<T, T>>;
  ```
  ```C++
  epvec<double>       // std::vector<std::pair<double, double>>
  ```