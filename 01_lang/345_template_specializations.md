## Explicit Template Specialization
*Full specialization*  

Belirli template argumani yada argumanlari icin derleyicinin bir specialization olusturmasi yerine bizim sagladigimiz kodun (specialization'in) kullanilmasi talimati verilmesini saglayan bir aractir.

```C++
// primary template for func<T>
template <typename T>
void func(T)
{
}

// explicit specialization for func<int>
template <>
void func(int) 
{
}
```
```C++
func(12);   // full spec.
func('A');  // primary
func(3.4);  // primary
```

**Motivasyon**
Bazi durumlarda template ile belirtilen kod, bazi acilimlar icin uygun olmayabilir:
```C++
// primary template
template <typename T>
T getmax(T x, T y) 
{
    return x > y ? x : y;
}
```
```C++
cout << getmax(10, 1235) << '\n';
cout << getmax("ayse", "zeliha") << '\n';
```
`"zeliha"` ve `"ayse"` karsilastirmasinda `const char*` turunden pointer adres karsilastirmasi yapilmaktadir. Bu durum icin ayri bir template specialization'i belirtilmelidir.

> :triangular_flag_on_post: 
> string literalleri `.data` segmentinde **static omurlu** olarak olusturulur.
  
Bu durumda kullanilabilecek farkli araclar:
1. Gercek bir fonksiyon yazilabilir.
2. Template overload edilebilir.
3. Explicit specialization ile `const char*` turu icin kullanilacak kod verilebilir.
   ```C++
   template <>
   const char* getmax(const char* p1, const char* p2) 
   {
       return std::strcmp(p1, p2) >= 0 ? p1 : p2;
   }
   ```
   
<!--  -->

**Kurallar**
* Ayni namespace icinde bulunmasi gerekir.
* Specialization'in primary template'i gorebilmesi gerekir. *Bildirim olarak gormesi yeterlidir.*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template<typename T>
  void func(T);
  
  template<>    // bu noktada func'in bir template oldugunun gorulmesi gerekiyor
  void func(int) {
      cout << "full spec for func<int>\n";
  }
  ```
  </details>
  <!--  -->
  
* Birden fazla explicit specialization bir arada olabilir.
* `template <>` ile bildirilir. Birden fazla template parametresi var ise **tum parametreler icin argumanlar** belirtilmelidir. *Bu nedenle full specialization denir.*

* Template secimi once primary templateler arasinda overload resolution'a uygun olarak yapilir, **secilen template'den kod uretilmesi gerektiginde** secilen template'e ait uygun bir explicit specialization var ise kullanilir.
  > :warning: 
  > Explicit specialization overload resolution'a ait bir mekanizma degil, bir template'den kod uretilmesi sirasinda kod secimini saglayan bir mekanizmadir.
  
  ```C++
  // primary template 1 (overload)
  template <typename T>
  void func(T) { cout << "1"; }
        
        // full spec for template 1, does not overload 
        template<>
        void func(int*) { cout << "2"; }
  
  // primary template 2 (overload)
  template<typename T>
  void func(T*) { cout << "3"; }
  
        // full spec for template 2, does not overload 
        template<>
        void func(int*) { cout << "4"; }
  ```
  Asagida bulunan `func` fonksiyonu `int*` ile cagrildiginda primary template'ler arasinda overload resolution sonucu 2. template secilir, ve `int*` explicit specialization'i kullanilir. 
  ```C++
  int* p = nullptr;
  func(p);  // 4
  ```

> :warning:   
> Fonksiyon sablonlari icin explicit specialization bazi durumlarda gorulmesi zor hatalara neden olabildiginden; programcilar fonksiyon sablonlarinda explicit specialization yerine template'leri overload etmeyi terchi ediyorlar.

* class template icin explicit specialization bildirimi:
  `Myclass<int>` icin **full speciazation** kodu kullanilan, diger turler icin **primary template** kullanilan bir ornek:
  ```C++
  template <typename T>
  class Myclass {
  public:
      Myclass() { 
          std::cout << "prmary\n";
      }
      void f1();
      void f2();
  };
  
  // Myclass<int> icin explicit (full) specialization
  template <>
  class Myclass<int> {
  public:
      Myclass() { 
          std::cout << "Myclass<int>\n";
      }
      void f3();
      void f4();
  };
  ```
  ```C++
  Myclass<char> m1;       // primary
  Myclass<short> m2;      // primary
  Myclass<int> m3;        // explicit
  Myclass<double> m4;     // primary
  ```
  </details>
  <!--  -->

* Bir sinif sablonu icin bildirilen explicit specialization, **farkli bir interface**'e sahip olabilir.
* Bir sinif sablonu icin explicit specialization bildirilebilmesi icin primary template bildirimi yeterlidir, tanimi zorunlu degildir.
  ```C++
  template<typename T>
  class Myclass;
  
  template<>
  class Myclass<int>{
    // ...
  };
  ```
  ```C++
  Myclass<int> x;
  ```

[Soru: Dongu kullanmadan 0'dan 100'e kadar sayilarin yazdirilmasi](sorular/soru20.cpp)

## Partial Template Specialization
*Kismi/parsiyel*

Explicit specializationdan farki bir ture ait degil, bir tur argumani gruba ait speciazlication verilmektedir. Ornegin pointer turleri icin, dizi turleri icin gibi.

```C++
// primary class template
template <typename T>
struct Myclass {
    Myclass() {
        cout << "primary template\n";
    }
};

// partial specialization for class template Myclass where T is a pointer type
template <typename T>
struct Myclass<T*> {
    Myclass() {
        cout << "partial specialization Myclass<T*>\n";
    }
};
```
```C++
Myclass<int> n1;        // primary template
Myclass<double> n2;     // primary template
Myclass<int*> n3;       // partial specialization for Myclass<T*>
Myclass<int**> n4;      // partial specialization for Myclass<T*>
Myclass<string*> n5;    // partial specialization for Myclass<T*>
```

* Sadece **sinif sablonlari** icin kullanilabilir. Fonksiyonlar icin kullanilamamaktadir.
* Bir sinif sablonu icin bildirilen partial specialization, **farkli bir interface**'e sahip olabilmektedir.
* Bir sinif templateine birden fazla ayri partial specializationlar tanimlanabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  struct Nec {
      Nec() {
          std::cout << "primary\n";
      }
  }; 
  
  // (1) Pointer turleri icin Nec sinifi partial specialization'i:
  template <typename T>
  struct Nec<T*> {
      Nec() {
          std::cout << "partial Nec<T*>\n";
      }
  };
  
  // (2) Referans turleri icin Nec sinifi partial specialization'i:
  template <typename T>
  struct Nec<T&> {
      Nec() {
          std::cout << "partial Nec<T&>\n";
      }
  };
  
  // (3) Dizi turleri icin Nec sinifi partial specialization'i:
  template <typename T>
  struct Nec<T[]> {
      Nec() {
          std::cout << "partial Nec<T[]>\n";
      }
  };
  
  // (4) 5 elemanli dizi turleri icin Nec sinifi partial specialization'i:
  template <typename T>
  struct Nec<T[5]> {
      Nec() {
          std::cout << "partial Nec<T[5]>\n";
      }
  };
  ```
  ```C++
  Nec<int>                    // primary
  Nec<double>                 // primary
  Nec<int*>                   // (1) partial Nec<T*>
  Nec<int**>                  // (1) partial Nec<T*>
  Nec<std::string*>           // (1) partial Nec<T*>
  Nec<int&>                   // (2) partial Nec<T&>
  Nec<double&>                // (2) partial Nec<T&>
  Nec<int[]>                  // (3) partial Nec<T[]>
  Nec<double[5]>              // (4) partial Nec<T[5]>
  ```
  </details>
  <!--  -->

* Partial specialization taniminda template argumanlari da kullanilabilmektedir.
  *Ikinci template argumani int ise partial, degilse primary kullanilanilsin*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T, typename U>
  struct Nec {
      Nec() {
          std::cout << "primary\n";
      }
  };
  
  template <typename T>
  struct Nec<T, int> {
      Nec() {
          std::cout << "partial\n";
      }
  };
  ```
  ```C++
  Nec<double, long>       // primary
  Nec<int, long>          // primary
  Nec<float, char>        // primary
  Nec<float, int>         // partial
  Nec<int, int>           // partial
  ```
  </details>
  <!--  -->
  
  *`T` ve `U` turleri ayni ise partial, degilse primary template kullanilsin.*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T, typename U>
  struct Nec {
      Nec() {
          std::cout << "primary\n";
      }
  };
  
  template <typename T>
  struct Nec<T, T> {
      Nec() {
          std::cout << "partial\n";
      }
  };
  ```
  ```C++
  Nec<double, long>       // primary
  Nec<int, long>          // primary
  Nec<float, char>        // primary
  Nec<float, int>         // primary
  Nec<int, int>           // partial
  Nec<char, char>         // partial
  ```
  </details>
  <!--  -->

* Primary template parametre sayisindan **daha fazla sayida arguman** ile partial specialization olusturulabilir.  
  *Template argumanlarinin ikiside `pair` tuirunden olan partial specialization tanimi*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T, typename U>
  struct Nec {
      Nec() {
          std::cout << "primary template\n";
      }
  };
  
  template <typename T, typename U, typename V, typename M>
  struct Nec<pair<T,U>, pair<V,M>> {
      Nec() {
          std::cout << "partial specialization\n";
      }
  };
  ```
  ```C++
  Nec<int, double>                                  // primary
  Nec<pair<int, double>, pair<char, long>>          // partial
  ```

  </details>
  <!--  -->
  




