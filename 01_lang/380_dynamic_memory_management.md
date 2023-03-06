# Dynamic Memory Management

Dinamik bellek yonetimi, dinamik omurlu bir nesnenin bellek alaninin elde edilmesi/iadesinin yonetimidir. Bellek tahsisi/iadesi, calisma zamaninda belirlenmektedir. Cogunlukla polymorhic siniflar icin dinamik tur bilgisi de calisma zamaninda elde edilebilmektedir.

> :warning: Dinamik bellek yonetimi ile [dinamik omurlu nesne](../01_lang/050_basics.md#dynamic-storage) kavramlari birbiri ile iliskili ancak farkli kavramlardir.

Dinamik omurlu bir nesnenin hayata getirilmesi `new` ifadeleri, hayatlarini sonlandirmak `delete` ifadeleri ile belirtilmektedir. `operator new` ve `operator delete` fonksiyonlari ise dinamik bellek tahsisi ve iadesi amaciyla kullanilir.

Dinamik omurlu olarak olusturulan nesneler isi bittiginde `delete` edilmelidir. Aksi halde sinifin destructor'i cagrilmayacagi icin **memory leak**'in yani sira **resource leak** olusma ihtimali de bulunmaktadir.

## `operator new`/`operator delete` fonksiyonlari
```C++
void* operator new(std::size_t sz);
void operator delete(void* ptr) noexcept;
```
`operator new` fonksiyonu arguman olarak verilen deger kadar byte bellek tahsisini saglayan bir fonksiyondur.

`operator delete` fonksiyonu, `operator new` fonksiyonu ile tahsis edilmis bir bellek alanini tekrar kullanimi icin iade eder.

* Overload edilebilmektedirler.
* `operator new` fonksiyonu basarisiz olursa `std::bad_alloc` turunden bir exception firlatir.

<!--  -->

### Overloading `operator new`/`operator delete`

* `operator new`'in `void*` parametreli bir fonksiyonu overload edilemez.
  ```C++
  void* operator new(void* vptr, std::size_t sz);
  ```

* Global olarak overload edilebilmektedirler.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  [Ornek: Overloading global operator new/delete function](res/src/dmm01.cpp)
  ```C++
  void* operator new(std::size_t sz)
  {
      std::cout << "operator new called for the size of " << sz << '\n';
  
      if (sz == 0)
          ++sz;
  
      void* ptr = std::malloc(sz);
      if (!ptr)
          throw std::bad_alloc{};
  
      std::cout << "the address of the allocated block is " << ptr << '\n';
      return ptr;
  }
  
  void operator delete(void* ptr) noexcept
  {
      std::cout << "operator delete called for address " << ptr << '\n';
      std::free(ptr);
  }
  ```
  </details>
  <!--  -->
  
* Bir sinif turune ozellestirilmis olarak sinifin static uye fonksiyonu olarak bildirilebilmektedirler.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  [Ornek: Overloading class member operator new/delete function](res/src/dmm02.cpp)
  ```C++
  class Myclass {
  public:
      void* operator new(size_t);
      void operator delete(void*);
  private:
      unsigned char buffer[1024]{};
  };
  ```
  ```C++
  auto m = new Myclass;
  auto m2 = new ::Myclass;        // global new ile cagrilmasi
  ```
  </details>
  <!--  -->
  
[Psuedocode: new_handler impl](res/src/dmm03.cpp)  
[Psuedocode: new_handler usage demo](res/src/dmm04.cpp)  

Farkli isteklere yonelik farkli allocator kullanma stratejisi yerine gore verimi arttirabilir. Ornegin; cok kucuk nesneler allocate edilmesi icin ozel bir mekanizma kullanilmasi. [[bknz:SBO vb.](../01_lang/999_kavramlar.md#small-buffer-optimization-sbo)]

### `operator new`/`operator delete` vs `malloc`/`free` 
`malloc`/`free` fonksiyonlari C dilinde bellek yonetimi icin kullanilmaktadir.
```C++
void* malloc(std::size_t);
void free(void *p);
```
* Her iki fonksiyon cifti de bellek tahsisi ve iadesi icin kullanilir. 
* `malloc` fonksiyonu basirisiz oldugunda `NULL` geri doner iken, `operator new` fonksiyonu `std::bad_alloc` turunden bir exception throw etmektedir.

> :warning: `malloc` ile tahsis edilen bellek alani `free` ile, `operator new` ile tahsis edilmis bellek alani `operator delete` ile iade edilmelidir.


## `new` ve `delete` ifadeleri

**Bir sinif nesnesinin dinamik olarak hayat getirilmesi**  
```C++
A* aptr = new A{ 12 };      // operator new(sizeof(A))
```
`new A` ifadesi karsiligi yapilan islemler sirasiyla:
1. `operator new(sizeof(A))` cagrisi  
   Ismi `operator new` olan global fonksiyonuna arguman olarak `sizeof(A)` degeri ile cagri yapilir. Eger cagri sonucu basarili ise tahsis edilen `sizeof(A)` buyuklugunde bir bellek alaninin `void*` turunden adresini doner. Eger cagri basarisiz olursa, `std::bad_alloc` turunden bir exception firlatilir.
2. `void*` turunden adres degeri, `A*` turune donusturulur. Bu adres degeri `this` pointer'i olarak kullanilir.
3. `this` pointerinin gosterdigi bellek alaninda `A` sinifinin constructor'ina verilen argumanlar ile cagri yapilarak nesne olusturulur.
   
> :triangular_flag_on_post: Sembolik olarak `new A(12)` ifadesi:
> ```C++
> ((A*) operator new(sizeof(A)))->A(12); 
> ```

**Dinamik omurlu bir sinif nesnesin hayatinin sonlandirilmasi**  
```C++
delete aptr;
```
`delete aptr` ifadesi karsiligi yapilan islemler sirasiyla:
1. `aptr` adresinde bulunan nesnenin destructor'ina cagri yapilir.
2. `operator delete` fonksiyonuna `aptr` argumani ile cagri yapilir.
   
> :triangular_flag_on_post: Sembolik olarak `delete p` ifadesi:
> ```C++
> aptr->~A();
> operator delete(aptr);
> ```

### Array new/delete
```C++
new T[n];
delete[] p;
```

> :warning: `new T[n]` ile tahsis edilen bellek alaninin `delete` ifadesi ile kullanimi **UB**'dir, `delete[]` kullanilmalidir.

[Ornek](res/src/dmm05.cpp)  

### const new
```C++
const auto* ptr = new const A{};
```

### placement new
Bir nesneyi verilen bir adres alaninda olusturmak icin kullanilir.
```C++
unsigned char storage[sizeof(Myclass)];
auto p = new (storage) Myclass;
```
`new` ifadesi bir adres degeri ile olusturulmus ise `operator new(void*, size_t)` fonksiyonuna cagri yapilir, ve sinifin ctor'u cagrilir.

> :warning: Storage alani dinamik bir bellek alani degil ise, `delete` ifadesi kullanilmamalidir.

Bir new ifadesi ile olusturulmus bir sinif nesnesinin adresinde `delete` ifadesi kullanilmadigi durumda **sinifin dtor'u cagrilmayacaktir**. Bu durumlarda dtor programci tarafindan cagrilmalidir.
```C++
p->~Myclass();
```

[Ornek: automatic storage alaninda dinamik bir nesne olusturma](res/src/dmm06.cpp)  

### nothrow new
```C++
auto p = new (std::nothrow) Myclass;
```
Bazi ortamlarda, ornegin RT embedded cihazlarda, new ifadesi basarisiz olmasi durumunda exception handling toleransi olmayabilir. Bu durumlarda `operator new`'in exception gondermemesi yerine `nullptr` geri dondurtulmesi saglanabilmektedir.

> :triangular_flag_on_post: `std::nothrow`, `<new>` baslik dosyasinda tanimli bos bir sinif olan `nothrow_t` turunden *constexpr* bir degiskendir.
> ```C++
> class nothrow_t {};
> constexpr nothrow_t nothrow;
> ```

[Ornek](res/src/dmm07.cpp)

