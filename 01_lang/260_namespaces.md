# Namespaces

[cppreference.com: Namespaces](https://en.cppreference.com/w/cpp/language/namespace)

C dilinde tum bildirimler, global isim alaninda bulunur ve global isim alanindaki isimler cakisabilir.

C++ dilinde farkli modullerden gelen isimlerin cakismasinin onune gecebilmek icin namespace araci bulunur.

```C++
namespace NS {

}
```
* namespace bildirimi sonunda `;` kullanilmaz.
* Isim alaninin bir ismi olmak zorunda degildir. [[bknz: Unnamed namespace](260_namespaces.md#unnamed-namespace)]

> **Not**
> Standart library tanimlarinin tamami `std` namespace'indedir.
> *Turkce'de 'setede', Ingilizce'de 'sutud' olarak okunur.*

## Genel Kurallar
* Bir namespace icersinde global namespace'de yapilabilen her sey yapilabilir.
* C++ dilinde namespace icin bir **access control** bulunmamaktadir.
* Namespace icinde olusturulan degiskenler **statik omurlu**dur ve **global** alanda olusturulur.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace NS {
    int x;  // x, global statik omurlu bir degiskendir.
  }
  ```
  </details>
  <!--  -->

* Namespace ya global namespace'de bulunabilir yada baska bir namespace icinde bulunabilir.
  *Baska bir namespace icinde bulunan namespace'e **[nested namespace](260_namespaces.md#nested-namespace)** denir.*
* Namespace'ler **kumulatif** ozellige sahiptir.
  *Derleyici bir namespace ile karsilastiktan sonra ayni isimli namespace ile karsilasirsa ayri bir namespace olusturmaz, birlestirir. Bu ozellik farkli baslik dosyalarinda ayni namespace kullanilabilmesini saglamaktadir.*
* Farkli namespace'lerde ayni isimler farkli varliklar icin cakisma olmadan kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  double x;

  namespace NS {
      int x = 5;
  }

  namespace AnotherNS{
      void x();
  }
  ```
  </details>
  <!--  -->
* Bir namespace icerisinde ayni isim birden fazla varliga verilemez.
* Ayni namespace icersindeki isimler nitelenmeden kullanilabilir. Ancak, fonksiyonun geri donus turu namespace'e dahil degildir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace NS {
    class Nec{};
    class Data{};
    Nec func(Nec x);
  }
  ```
  `x` parametresi namespace'e dahil olmasindan dolayi nitelenmesi zorunlu degildir. Ancak geri donus degeri namespace icinde olmadigi icin nitelenmek zorundadir:
  ```C++
  pro::Nec pro::func(Nec x)     // pro namespace'i icindeki func sinifinin tanimi
  {
    Data d;
  }
  ```
  auto trailing return type namespace icinde kabul edilir:
  ```C++
  auto pro::func(Nec x) -> Nec
  {
    Data d;
  }
  ```
  </details>
  <!--  -->

**Namespace icinde isim arama**
* Bir namespace icinde bulunan bir ismi derleyiciye aratip buldurmak icin:
  1. Binary `::` operatoru ile nitelenerek
  2. Ayni namespace icine alinarak
  3. using declaration
  4. using namespace (directive) declaration
  5. Argument dependant lookup (ADL)

* Namespace icinde ismi nitelemeden kullanmanin yollari:
  1. using declaration
  2. using namespace (directive) declaration
  3. Argument Dependant Lookup (ADL)

* Namespace icinde isim arama yapilirken henuz declare edilmemis bir isim *global namespace'de oldugu gibi* bulunamaz. Ismin nitelenmis olmasi bu durumu degistirmez.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace NS {
    void foo();

    void func() {
        foo();      // gecerli
        bar();      // gecersiz: cunku henuz declare edilmedi
        NS::bar();  // gecersiz: cunku henuz declare edilmedi
    }

    void bar();
  }
  ```
  </details>
  <!--  -->


## binary scope resolution `::` operatoru
Operand olarak verilen ismi global namespace icinde aranmasini saglayan bir binary operatordur. Overload edilemez.
**Ornek**
```C++
int x = 10;

namespace ali {
    int x = 20;
    void func()
    {
        {
            {
                x = 5;          // ali namespace'i icindeki x
                ali::x = 5;     // ali namespace'i icindeki x
                ::x = 5;        // global namespace'deki x
            }
        }
    }
}
```

## `using` declaration
Namespace ismi ile birlikte nitelenmis bir isim bildirimidir.

```C++
using std::cout;
using std::cin, std::endl;    // [C++17]
```

* using declaration bir bildirimdir ve her bildirim gibi bir scope'u vardir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  void foo() {
    using std::cout;
    cout << 1;  // gecerli
  }

  void bar() {
    cout << 1;  // syntax error
  }
  ```
  </details>
  <!--  -->

  > **DIKKAT!**
  > `using` bildirimlerinin kapsamini mumkun oldugunca kucuk tutulmasi tavsiye edilmektedir.

* using bildirimi ile sunulan isim bildirimin yapildigi isim alanina **inject** edilir.
  *Ayni scope'da bir isim sadece bir nesne icin kullanilabilir!*
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace nec
  {
      int x = 10;
  }

  int main() {
      using nec::x;     // nec::x ismi main fonksiyonuna inject edildi

      int x = 20;       // syntax error: scope icinde x ismi daha once bildirildi.
  }
  ```
  </details>
  <!--  -->


* Inject edilmis bir isim, baska bir namespace de **tekrardan inject** edilebilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali {
      int x = 4;
  }

  namespace can {
      using ali::x;
  }

  namespace eda{
      using can::x;
  }

  int main() {
      eda::x = 5;   // gecerli
  }
  ```
  </details>
  <!--  -->

  global namespace icin de ayni durum gecerlidir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  int x = 10;

  namespace ali
  {
      using ::x;    // gecerli
  }

  int main()
  {
      ali::x = 10;  // gecerli
  }
  ```
  </details>
  <!--  -->

* using ile inject edilmis ayni isimli fonksiyonlar, bildirildikleri scope icerisinde **overload olusturabilirlerdir**.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali {
      void func(int);         // (1)
  }

  namespace can {
      void func(int, int);    // (2)
  }

  void func();                // (3)

  int main() {
      using ali::func;
      using can::func;

      func(12);       // gecerli: overload olur, (1) cagrilir.
      func(1, 2);     // gecerli: overload olur, (2) cagrilir.
      func();         // gecersiz: name-hiding

      // Gecerli olmasi icin asagidakiler yapilabilir:
      ::func();       // (1) Nitelendigi icin direkt olarak globalde aranir.
      using ::func;   // (2) bildirim inject edilerek overload olusturulur
  }
  ```
  </details>
  <!--  -->

  > **Hatirlatma**
  > Isim arama, isim bulundugunda biter! Isim arama sonlandiginda kapsayan scope'lardaki bildirimler **name-hiding**e ugramis olur.


## `using namespace` bildirimi
Bir namespace icinde bulunan tum bildirimlerin bir scope icerisinde **gorunur kilinmasini** saglamaktadir.

```C++
using namespace std;
```

* using namespace declaration bir bildirimdir ve her bildirim gibi bir **scope'u vardir**.
* using namespace bildirimi ile bildirilecek namespace, bildirildigi yerde **gorunur olmali**dir.
* using namespace bildirimi, namespace icinde declare edilen nesneleri **sadece gorunur kilar**, inject etmez.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace nec {
    int x;
    int foo();
  }

  int main() {
    x = 5;              // syntax error: using namespace nec henuz bildirilmedi
    using namespace nec;
    x = 10;             // gecerli: nec::x
    foo();              // gecerli: nec::foo
    nec::foo();         // gecerli: nec::foo

    int x = 30;         // gecerli: using namespace inject etmez.
    std::cout << x;     // prints 30
  }
  ```
  </details>
  <!--  -->

* Birden fazla namespace bildirimi yapilmis olmasi; namespace iceriginde isim cakismasi olsa dahi inject etmemesinden dolayi hata olusturmaz.
  Ancak cakisan isim nitelenmeden kullanildiginda ambiguity olusabilir.
  > **Not**
  > Zaten namespace'in kullanim amaci, isim cakismalarini engellemekti. Bu nedenle global isim arama alaninda using namespace bildirimi yapilmasi tercihen onerilmez.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali {
    int x = 456;
  }

  namespace eda {
    double x = 4.9;
  }

  using namespace ali;
  using namespace eda;

  int main() {
    x = 45;         // gecersiz: ambiguity
    ali::x = 10;    // gecerli: ali namespace'inde aranacak
  }
  ```
  </details>
  <!--  -->

* using namespace bildirimi, namespaceler arasinda (global de dahil) ayni isimli fonksiyonlar arasinda overload olusturur.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali {
    void func(int);         // (1)
  }

  namespace eda {
    void func(int, int);    // (2)
  }

  using namespace ali;
  using namespace eda;

  int main() {
    func(12);   // gecerli: ali::func
    func(1, 2); // gecerli: eda::func
  }
  ```
  ```C++
  namespace ali {
    void func(int);     // (1)
  }

  using namespace ali;

  void func(double);    // (2)

  int main() {
    func(1234);   // ali::func
    func(3.14);   // ::func
  }
  ```
  </details>
  <!--  -->

* using namespace bildirimi, nested namespace'ler icinde de yapilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali {
      namespace veli{
          namespace can{
              int x;
          }
          using namespace can;
      }
      using namespace veli;
  }
  ```
  ```C++
  ali::veli::can::x = 10;   // gecerli
  ali::veli::x = 10;        // gecerli
  ali::x = 10;              // gecerli
  ```
  </details>
  <!--  -->


## Argument Dependat Lookup (ADL)
*Argumana bagli isim arama*


Eger bir fonksiyon cagrisinda arguman olan *bir ifadede yer alan bir isim* bir namespace icinde bildirilen bir ture iliskin ise (herhangi bir tur ile ilgili ise) fonksiyon ismi argumanin namespace'de de aranir. Bu durum diger tum argumanlar icin de gecerlidir.

> **Koenig Lookup**: (Andrew Koenig) ADL'in eski ismi.

```C++
namespace nec
{
    enum Color { red, green, blue};
    class Neco{};

    void func(Neco);
    void func(Color);
    void func(std::vector<Neco>);
}

int main()
{
    nec::Neco x;
    func(x);        // gecerli: x ismi nec namespace'ine ait bir isim
    func(nec::red); // gecerli: red ismi nec namespace'ine ait bir isim
    func(12);       // syntax hatasi: func ismi bulunamadi

    std::vector<nec::Neco> x;
    func(x);        // gecerli
}
```
ADL, ismi arama prosedurunden once ilgili namespace'i **sadece visible hale getirir**. ADL isim aramaya alternatif bir mekanizma degildir. Dolayisi ile isim arama yapilirken ADL'in bir sirasi yada onceliginden bahsedilemez.
<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
namespace nec {
    class A {};

    void func(A);
}

void func(nec::A);

int main() {
    nec::A a;

    func(a);    // syntax hatasi: ambiguity
                //   ADL ismi visible hale getirdi.

}
```
```C++
namespace nec {
    class A {};

    void func(A);
}

int main() {
    nec::A a;

    void func(int);
    func(10);   // gecerli
    func(a);    // syntax hatasi: name-hiding
}
```
</details>
<!--  -->

[[ADL Quiz](sorular/soru13.cpp)]


## Unnamed Namespace
*isimlendirilmemis isim alani*
```C++
namespace {

}
```
Eger bir kaynak dosyada isimlendirilmemis bir isim alani olusturulursa bu isim alani icindeki varliklar, **internal linkage**'a tabidir.

C'de global alanda kullanilan `static` anahtar sozcugu ile ayni gorevi yerine getirmektedir. Ancak, `static` anahtar sozcugu C++ dilinde turler ile birlikte kullanilamamaktadir.

```C++
int x = 10;             // external
const int cx = 0;       // internal (C'de external)
static int sx = 0;      // internal
static void func();     // internal
static class Myclass{}; // syntax error
```
```C++
namespace {
    int x = 10;         // internal
    int cx = 0;         // internal
    int sx = 0;         // internal
    void func();        // internal
    class Myclass{};    // internal
    class enum color{}; // internal
}
```
Isimsiz bir namespace'de tanimlanmis ogelerin nitelenmesine gerek yoktur.
```C++
x = 10;
::x = 20;
```
* Isimsiz namespaceler de **kumulatif** ozellige sahiptir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace{
    int x;
  }
  namespace{
    int y;
  }

  x = 10;
  y = 20;
  ```
  </details>
  <!--  -->


## Nested Namespace

```C++
namespace ali {
    namespace veli{
        namespace can{
            int x;
        }
    }
}
```
```C++
ali::veli::can::x = 10;
```

**Nested namespace icin eklenen yeni kurallar**
* [C++17] Oncesinde bir nested namespace kendisini kapsayan namespace icine yazilmasi gerekiyordu. Yeni syntax ile namespace henuz bildirilmemis olsa dahi asagidaki bicimde nested namespaceler olusturulabilme imkani olustu.
  ```C++
  namespace ali::veli::can {
      int c = 10;
  }

  namespace ali {
      int a;
  }

  namespace ali::veli {
      int v;
  }
  ```
  <details>
  <summary><b>Eskiden</b> (Click to expand)</summary>

  ```C++
  namespace ali {
      int a;
      namespace veli{
          int v;
          namespace can {
              int c = 10;
          }
      }
  }
  ```
  ```C++
  int main() {
      ali::a = 1;
      ali::veli::v = 2;
      ali::veli::can::c = 3;
  }
  ```
  </details>
  <!--  -->

* `using namespace` bildiriminde nested namespaceler de kullanilabilir
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>

  ```C++
  namespace ali::can::eda{
    int x = 10;
  }
  ```
  ```C++
  using namespace ali;
  can::eda::x = 20;
  ```
  ```C++
  using namespace ali::can;
  eda::x = 20;
  ```
  ```C++
  using namespace ali::can::eda;
  x = 20;
  ```
  </details>
  <!--  -->


## Inline namespace
namespace bildiriminde `inline` ise parent namespace'de `using namespace` bildirimi yapilmis gibi davranis gostermektedir.

```C++
namespace ali {
    inline namespace veli {
        int x;
    }
}
```
```C++
ali::x; // gecerli
```

<details>
<summary><b>Eski yontem:</b> (Click to expand)</summary>

```C++
namespace ali {
    namespace veli {
        int x;
    }
    using namespace veli;
}
```
```C++
ali::x; // gecerli
```

</details>
<!--  -->

* Oyle senaryolar var ki eski yontemde ADL'in devreye girmedigi ancak `inline` yapildiginda ADL'in devreye girdigi durumlar var.

* Versiyon kontrolu icin uygun bir arac haline gelmistir.

  Ornegin bir kutuphane implemantasyonda binary compability'i bozmadan kullanilan siniflarin namespace ile yonetilmesine olanak saglamistir.
  [Versiyonlama Ornegi](res/src/namespace_version_control.cpp)
  
* [C++20] ile soyle yazilabilmektedir
  ```C++
  namespace ali::veli:: inline eda {
    int x = 5;
  }
  ```

## Namespace Alias

```C++
namespace siemens_project_xyz_lib {
    int a;
}

namespace sms = siemens_project_xyz_lib;

siemens_project_xyz_lib::a = 20;
sms::a = 20;
```

**Motivasyon**
* `nec` namespace'i barindirdiklarini global namespaceden ayirmasina ragmen hala `nec` ismi baska bir isim ile cakismaya neden olabilir.
* Versiyon kontrolu icin inline namespace hala daha uygun olmasina ragmen, nested namespacelerin kisaltmasi olarak da kullanilabilir.
  ```C++
  namespace ali::veli::proj{
    class Myclass{};
  }
  
  int main() {
    namespace pro = ali::veli::proj;
    pro::Myclass m;
  }
  ```

  > **Not**
  > Template kodlarin kullanilabilmesi icin derleyici tarafindan kodlarin gorunmesi gerekmektedir. Bu nedenle template tanimlar .cpp dosyasinda belirtilemez.

  necati.h:
  ```C++
  namespace nec{
    template<typename T>
    void func(T x);

    namespace details {
        template<typename T>
        void func(T x) {

        }
    }
  }
  ```

  necati.h:
  ```C++
   namespace nec{
     template<typename T>
     void func(T x);
   }

   #include "necati_impl.hpp" // dosyanin sonunda
   ```
   necati_impl.hpp:
   ```C++
   namespace nec:: inline details {
       template<typename T>
       void func(T x) {

       }
   }
   ```

