# Pointers
*Adresses*

Bir nesnenin bellekteki yerini gosteren varliklardir.

Iki turde pointer bulunmaktadir.
1. Object pointers
2. Function pointers

Her ifadenin bir turu olmasi nedeniyle adress bilgisinin de bir ture sahip olmak zorundadir.

* Bir adres turu bir nesnenin turunden elde edilmektedir. `T` turunden olan bir nesnenin adresi `T*` olarak ifade edilir.
* Adres ifadeleri Lvalue yada Rvalue olabilir.
* Tum pointer turler ayni miktarda yer kaplamaktadir. Ancak object pointer ile function pointer farkli boyutlarda olabilir.
  ```C++
  sizeof(int*) == sizeof(char*) == sizeof(double*)
  ```

* `*` sadece onune geldigi ismi pointer turu olarak ifade eder.
  ```C++
  int* p1, p2, p3; // p1 = int*, p2 = int, p3 = int
  int x, *p, a[5], *pa[5], **ptr;
  ```
  Bu durum tures isim ile bildirimlerde gecerli degildir.
  ```C++
  typedef int* iptr;
  iptr p1, p2, p3; // hepsi int* turunden
  ```
  
* static omurlu pointer degiskenler `nullptr` olarak hayata baslarlar.
* otomatik omurlu bir pointer garbage value ile hayata baslarlar.
  
> [bknz: storage classes](090_storage_classes.md)

* Bir adres ifadesi ya **valid pointer**dir yada **invalid pointer**dir.

**Valid pointer**
Degeri kullanilabilir bir pointeri ifade etmek icin kullanilir.

* Hayati devam etmekte olan bir nesne adresi tutuluyorsa her zaman gecerlidir.
* Bir dizinin bitti yerin adres valid pointerdir.
  ```C++
  int a[5] = {0};
  int* p = &a[5];   // valid pointer
  ```
  > **DIKKAT!**
  > Bir pointer'in valid olmasi, adresdeki nesneye erisimin *  (dereferencing)* mumkun oldugu anlamina gelmemektedir.
  > ```C++
  > a[5];  // UB
  > ```

* Hic bir nesneyi isaret etmedigi garanti altinda olan pointerdir. **Null pointer** da denilir.

**Invalid pointer**
* Degeri garbage value olan bir pointer. **Wild pointer** olarak da isimlendirilir.
* Dizinin range'i disinda adresi gosteren pointer
  ```C++
  int a[10];
  a - 1;    // syntax olarak dogru anca invalid pointer degeri
  a + 15;   // syntax olarak dogru anca invalid pointer degeri
  ```
* Hayati sonlanmis bir nesnenin adresine sahip pointer. **Dangling pointer** olarak da isimlendirilir.

> **DIKKAT!**
> Invalid pointer kullanimi **UB**dir!

## Nullptr
<!-- TODO 8. Derste nullptr, NULL ve 0 arasindaki fark anlatiliyor, eksigi tamamla -->
`nullptr`'nin turu `nullptr_t`dir. Bu bir **pointer turu degildir**, ancak pointer turune **donusebilen** bir turdur.

---

## `&` operatoru
*addressof operator*

Bir nesnenin adres degerini uretmek icin kullanilir.

* Unary prefix bir operatordur.
* Operandinin lvalue expression olmasi zorunludur.
* Urettigi deger adres degeridir. 
  `T` turunden bir nesne operandi oldugunda `T*` turunden bir deger uretir.
* `&` ile olusturulan ifade rvalue expressiondir.

---

## `*` operatoru
*dereferencing operator*

Bir adres degerinde bulunan varliga erisim icin kullanilir.

* Unary prefix bir operatordur.
* Operandi adres turunden olmak zorundadir.
* `*` ile olusturulan ifadenin urettigi deger lvalue expressiondir.
* Degeri `nullptr` olan bir pointer, gecerli bir pointer olmasina ragmen **dereference edilmemelidir**.

---

* Aritmetik turlerden adres turlerine implicit donusum yoktur.
  ```C++
  int x = 10;
  int* p = x;     // syntax error
  ```
  
* Farkli adres turleri arasinda implicit donusum yoktur.
  ```C++
  int x = 10;
  char* p = &x;   // syntax error 
  ```
  
## Pointer aritmetigi

* Bir adres tipi ile tamsayi toplanirsa sonuc adres turunden olusur.
  ```C++
  T* + int => T*
  ```
* Iki pointer adresi birbiri ile toplanamaz.
  ```C++
  T* + T* // syntax hatasi
  ```
* Ancak iki pointer adresi birbirinden cikarilabilir. Ifade sonucu uretilen deger `ptrdiff_t` turundendir. Tipik olarak `int`e tures isimdir.
  ```C++
  T* - T* => ptrdiff_t 
  ```
## functions returns an address
Bir fonksiyon 3 farkli sekilde gecerli adres donebilir.
1. Static omurlu nesne adresi
   * global nesne adresi
   * static yerel degisken adresi
   * string literali
2. Dinamik omurlu nesne adresi
3. Cagirandan aldigi adresi gondermesi

> **DIKKAT!**
> auto omurlu nesneler pointer olarak dondurulmemelidir!
> [Ornek](res/src/pointers01.cpp)

## Pointers ve `const`

<!-- TODO Derslerden notlari tamamla, bi yerde anlatiliyordu ama neresiydi? -->
```C++
int x = 10;

int const * p1 = &x;        // low-level const: p1 is pointer to const int
int * const p2 = &x;        // top-level const: p2 is const pointer to int
int const * const p3 = &x;  // p3 is a const pointer to const int
```

* Bir tur-es ismi bir pointer turune tur-es isim ise `const` anahtar sozcugu ile bildirimi **top-level const**dur.
  ```C++
  typedef int* iptr;    // yada using iptr = int*;
  
  int x = 10, y = 20;
  
  const iptr p = &x;    // int* const p
  *p = 56;      // gecerli
  p = &y;       // gecersiz, p top-level const
  
  ```