# Nested Types
*Icsel turler*
*(type member == member type == nested type)*

Tanimi bir sinif icerisinde yapilan turlerdir. Bu turler asagidakilerden biri olabilir:

1. Bir sinif bildirimi / tanimi
3. Bir enum
4. Bir tures ismi bildirimi

```C++
class Myclass {
public:
  typedef int Word;                       // type alias bildirimi
  using Word = int;
    
  enum class Color {gray, blue, black};   // enum bildirimi
    
  class Nested {};                        // sinif tanimi
  class AnotherNested;                    // forward declared
private:
  class PrivNested {};
};
```

Eger bir sinif nested olarak olusturulmus ise:  

* **Scope**: Nested types, tanimli oldugu class scope'a aittir.
* **Erisim kontrolu**: `PrivNested` turunu sadece `Myclass` ve tanimli friendleri kullanabilir.

**Name lookup**

> **DIKKAT!**
> Siniflarin **uye fonksiyonlarinin icinde** kullanilan isimlerin aranmasi ile **sinifin tanimi icinde** kullanilan isimlerin aranmasi birbirinden farklidir.  


* Eger bir name-hiding soz konusu degil ise; bir fonksiyon tanimi icinde sinifin bildirim sirasindan bagimsiz olarak isimler bildirilmeden kullanilabiliyor. Ancak, nested type icin bildirim sirasi, **bildirildikleri yerden sonra tanimli** olmalarindan dolayi, onem arz etmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass{
  public:
    void foo();
    void baz() {
      bar();   // gecerli isim arama
      mx++;    // gecerli isim arama
    }
    void bar();
  private:
    int mx;
  };
  ```
  ```C++
  void Myclass::foo() {
    bar();    // gecerli isim arama
    mx++;     // gecerli isim arama
  }
  ```
  Isim arama yapilan bildirim class scope icinde bulunmasindan dolayi `x` taniminda bulunan `foo` ismi henuz tanimlanmadigi icin bulunamayacaktir:
  ```C++
  class Myclass {
  public:
    inline static int x = foo();    // syntax error: identifier "foo" is undefined
    static int foo();
  };
  ```
  
  </details>
  <!--  -->
  
  Yukaridaki ornege benzer olarak class scope icinde henuz bildirilmemis bir nested type da *nitelenmis bir isim olsa dahi* bildiriminden once bulunamamaktadir:
  ```C++
  class Myclass {
  public:
    Word wm;            // syntax error: class "Myclass" has no member "Word"
    Myclass::Word wm2;  // syntax error: class "Myclass" has no member "Word"
    typedef int Word;
  };
  ```

* Class scope icinde de bildirim sirasina gore name-hiding olusabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  struct Word{};
  
  class Myclass {
  public:
    Word wm1;           // wm1 = struct Word
    typedef int Word;
    Word wm3;           // wm2 = int
    Myclass::Word wm4;  // wm3 = int
  };
  ```
  Yukaridaki ornekte `Word wm1` ifadesinin turu `struct` olacaktir, cunku isim arama yapilirken *class scope'da bildirilmis olmasina ragmen* henuz `typedef` bildirimi yapilmamistir. Bunun yani sira, `typedef` bildiriminden sonra `struct` bildirimi name-hiding'e ugradigi icin `wm2` ifadesinin turu `int` olacaktir:
  </details>
  <!--  -->
  
* Nested type, enclosing type'in `private` alanina erisebilir. Ancak enclosing type, nested class'in `private` alanina erisemez. 
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass { 
    class PrivNested{
      static void foo() {
        mx = 10;            // gecerli
        my = 10;            // gecerli
      }
      
      static int my;
    };
    
    void f() {
      mx = 10;              // gecerli
      PrivNested::my = 10;  // syntax error: foo is inaccessible
    }
    
    static int mx;
  };
  ```
  </details>
  <!--  -->

* Ifade icinde bir ismi kullanmadan varligi **tur cikarimi** ile elde edilirse `private` alanda bulunan ture erisilebilmektedir.
  *Isim yoksa erisim kontrolu de yok!*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass { 
    class PrivNested{};
  public:
    static PrivNested foo();
  };
  ```
  `PrivNested` nested type, private alanda olmasindan dolayi normalde disaridan erisim bulunmamaktadir.
  Tuhaf ancak `PrivNested` isimi ifade icinde kullanilmadigi icin erisim var:
  ```C++
  Nec::PrivNested nx;       // gecersiz: PrivNested is inaccessible
  auto x = Myclass::foo();  // gecerli
  ```
  [bknz: auto trailing return type](900.md#auto-trailing-return-type)
  </details>
  <!--  -->
  
* Fonksiyonun ici, *ister `inline` olsun ister olmasin*, class scope'a dahildir. Ancak geri donus turu, *[auto trailing return type](900.md#auto-trailing-return-type) istisna olmak uzere*, class scope'a dahil degildir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
  public:
    class Nested {};
    
    void foo(Nested);
  };
  ```
  ```C++
  void Nec::foo(Nested x) {     // gecerli
    Nested y;                   // gecerli
  }
  ```
  Ancak, **geri donus turu** nitelenmek zorundadir:
  ```C++
  class Myclass {
  public:
    class Nested {};
    
    Nested foo();
  };
  ```
  ```C++
  Nested Nec::foo() {           // syntax error
  }
  ```
  ```C++
  Nec::Nested Nec::foo() {      // gecerli
  }
  ```
  Istisna: auto trailing return type
  ```C++
  auto Nec::foo() -> Nested {   // gecerli
  }
  ```
  </details>
  <!--  -->
  

* Nested type'a iliskin tanimlar sinif blogu icinde yapilamaz.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Myclass {
    struct Nested {
      void foo();
    };
    
    // foo islevi burada tanimlanamaz!
  };
  ```
  </details>
  <!--  -->





## **Pimple idiom**
*Pointer Implementation idiom/handle body idiom/cheshire cat idion/opaque pointer idiom)*

Bu idiom **sinifin `private` bolumunu gizleme**ye yonelik bir tekniktir. 

<!-- TODO Ders 18: 16:00:00 -->

Sinifin `private` bolumunun baslik dosyasinda yer almasi bir takim dezavantajlar olusturabiliyor. 

* Compile isleminin suresinin uzamasina neden olur.
  Bir sinif icinde kullanilan sinif turunen isimlerin complete type olmasi gerekmektedir. Bu nedenle kullanilacak turlerin bildirimlerinin bulundugu baslik dosyalari eklemesi gerekmektedir.
  
* [ABI](999_kavramlar.md#abi) compability saglanamayabilir.
  Baslik dosyasida bildirilen siniflar degisiklige ugradiginda kullanici dosyalarin tekrar derlenmesi gerekmektedir.

Avantajlar:
* Private ogelerin gizlenmesi
* ABI Compability: Pointer kullanimi nedeniyle binary compatibility etkilenmiyor, cunku pointerlarin boyutu aynidir.
* Sinifin tasima islemleri daha sade
  *Tek bir ptr degeri tasiniyor.*

Dezavantajlar:  
* Sinif fazladan bir pointer'a sahip olmaktadir.
* pimpl nesnesi dinamik olarak olusturulmasi nesne olusturma ve yokedilme maliyetini yukseltmektedir.

[Ornek: Pimpl idiom (raw pointer)](res/src/203_type_member/piml_idiom01/)
[Ornek: Pimpl idiom (smart pointer)](res/src/203_type_member/piml_idiom03/)
<!-- TODO res/src/203_type_member/piml_idiom03/ icin unique_ptr ile implement et -->

> **Not**
> `pimpl` nesnesinin dinamik allocation ile kullanilmasi zorunlu degildir. 

## Fast pimple idiom
<!-- TODO herb sutter'in makalesi incelendikten sonra eklenecek -->
[https://herbsutter.com/gotw/](https://herbsutter.com/gotw/)
[bknz: GotW#028 (Guru of the Week)](http://www.gotw.ca/gotw/028.htm)
[bknz: Placement new](res/src/placement_new01.cpp)
[Ornek: Fast pimpl idiom](res/src/203_type_member/piml_idiom02/)


