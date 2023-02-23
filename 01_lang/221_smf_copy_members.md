## Copy Members

### **Value Semantics**

Value semantic kavramini destekleyen turler icin; bir nesneyi, baska bir nesne ile hayata getirdiginizde kendisine atama yapilan nesne diger nesnenin degerini alir.
```C++
x = y
``` 
Deger kopyalama isleminden sonra:
* `x` ile `y`'nin degerleri ayni olmalidir.olacaktir
* `x`'in degeri degisirse `y` etkilenmemelidir.
* `y`'in degeri degisirse `x` etkilenmemelidir.


### Copy Constructor
*kopyalayan kurucu islev*

Bir sinif nesnesi hayata getirilirken, degerini ayni turden bir baska sinif nesnesinden almasi icin `copy ctor` cagrilir.

```C++
class Myclass {
    Myclass(const Myclass&);
};
```

**Hangi senaryolarda bir sinif nesnesi copy ctor ile olusturulur:**
1. Dogrudan bir sinif nesnesini, baska bir nesneye arguman olarak verilerek hayata getirildiginde
   ```C++
   Myclass x;
   Myclass y1 = x;  // copy ctor cagrilir
   Myclass y2(x);   // copy ctor cagrilir
   Myclass y3{x};   // copy ctor cagrilir
   ```
2. Call by value parametreli fonksiyon cagrisinda arguman olarak verildiginde
   ```C++
   void foo(Myclass m);
   ```
   ```C++
   Myclass x;
   foo(x);          // copy ctor cagrilir
   ```
   [Ornek](res/src/smf_copy_ctor01.cpp)
3. Bir fonksiyonun geri donus turu olarak kullanildiginda  
   *Eger bir optimizasyon soz konusu degilse*
   ```C++
   Myclass foo()
   {
        Myclass m;
        return m;
   }
   ```
   ```C++
   auto x = foo();  // copy ctor cagrilir
   ```

Eger uygun kosullar saglaniyor ise derleyici implicit olarak bir copy ctor default edecektir. Derleyici tarafindan default edilen copy ctor; sinifin `non-static public inline` uye fonksiyonudur.
```C++
class Myclass {
    A ax;
    B bx;
    C cx;
};
```
Derleyici tarafindan default edilen copy ctor asagidaki gibidir:
```C++
Myclass(const Myclass& other) : ax(other.ax), bx(other.bx), cx(other.cx) {}
```
`y`'nin copy ctor'u `x` argumani ile cagrilir:
```C++
Myclass x;
Myclass y = x;
```
[Ornek: defaulted copy ctor](res/src/smf_copy_ctor02.cpp)

**Bir kaynak yoneten nesnenin default copy ctor ile kopyalanmasinin problemleri**
[String Sinifi: implicitly defaulted copy ctor (Shallow copy)](res/src/smf_copy_ctor03.cpp)

String sinifi orneginde, sinifin copy ctor'u derleyici tarafindan implicit olarak default edildi. Ornekteki gibi bir kaynak yoneten nesnenin kopyalanmasi durumunda, kaynak [shallow copy](020_temel_kavramlar.md#terminoloji) olarak kopyalanacagi icin dtor'lardan biri calistiginda asagidaki durumlar olusacaktir:
1. **Value semantik korunamayacak**
   Nesnelerden birinin dtor'u calistiginda, iki nesnenin de kaynagi yok edilecek.
2. **Dangling pointer kullanimi**
   Nesnelerden birinin dtor'u calistiginda, diger nesnenin icindeki pointer dangling durumuna dustugu icin bu nesnenin dtor'u calistiginda **UB** olusacak!

**Ornek**
```C++
#include "string.h"

void foo(String y);

String x{"log.txt"};
foo(x);
```
Boyle bir durumda value semantiginin korunmasi isteniyor ise, [deep copy](020_temel_kavramlar.md#terminoloji) uygulanmasi gerekmektedir.

[String Sinifi: User-defined copy ctor (Deep copy)](res/src/smf_copy_ctor04.cpp)

> **Person sinifinin copy ctor'unu yazmamiz gerekir miydi?**
> ```C++
> class Person{ 
>     String mname;
> };
> ```
> `Person` sinifinin default ctor'u, `mname`'i kopyalarken `String` sinifinin copy ctor'unu cagiracagi icin gerekmezdi.

> **Not**  
> Bazi sinif nesneleri icin bir nedenden dolayi copy ctor **user defined-deleted** olarak kopyalamaya karsi kapatilabilir. 
> *Dipnot: Eski C++'da bir fonksiyon silinemedigi icin kopyalamaya kapatilmak istenen sinifin copy ctor'u private yapiliyordu.*


> **DIKKAT!**
> Tipik olarak eger bir sinifa destructor yazilmasi gerekiyor ise, copy ctor'da **yazilmali**dir yada **delete** edilmelidir.

### Copy Assignment
*kopyalayan atama fonksiyonu*

Hayatta olan bir sinif nesnesinin, degerini hayatta olan baska bir sinif nesnesine kopyalama ile atanmasi durumunda sinifin `operator=` fonksiyonu cagrilir.

```C++
class Myclass {
    Myclass& operator=(const Myclass&);
};
```

* Bir sinif nesnesine ayni turden bir sinif nesnesi atandiginda cagrilir.
* Copy ctor'dan farki, iki nesne de hali hazirda olusturulmustur. **Bu bir ctor degil!**

Eger copy assignment operator fonksiyonu implicitly declared ise derleyici sinifa `non-static public inline` bir copy assignment member fonksiyonu yazar.
```C++
class Myclass {
    A ax;
    B bx;
    C cx;
};
```
Derleyici tarafindan default edilen copy assignment asagidaki gibidir:
```C++
Myclass& operator=(const Myclass& other) 
{
    ax = other.ax;
    bx = other.bx;
    cx = other.cx;
    
    return *this;
}
```
`y`'nin copy assignment uye fonksiyonu `x` argumani ile cagrilir:
```C++
Myclass x, y;
y = x;          // x.operator=(y);
```

* Bir sinif nesnesine ayni turden bir sinif nesnesi atandiginda cagrilir.
* Copy ctor'dan farki, iki nesne de hali hazirda olusturulmustur. **Bu bir ctor degildir!**
* Geri donus turu `T&`'dir.

**Neden assignment operatoru donus degeri lvalue ref?**
* C++'da `x = y` ifadesi bir `lvalue expr`'dir. Atama islemi tum degerler icin *(primitive turler dahil)* boyledir.
* `operator=` fonksiyonun geri donus degeri ancak bir lvalue ise olusturdugu ifade de lvalue expression olur.

> **Hatirlatma**    
> C'de ve C++'da;
> 
> * Atama operatorunun urettigi deger, **nesneye atanan deger**dir:
>   *Dipnot: Atanmakta olan deger degil, conversion'da farkli olabilir*
>   ```C++
>   while((c = getchar()) != '\n');
>   ```
> * Right associative'dir. *(Sagdan sola oncelik yonune sahiptir)*  
>   ```C++
>   x = y = z = t = 10; // x = (y = (z = (t = 10)));
>   ```

[Ornek: Date sinifi](res/src/smf_copy_assign01.cpp)
[Ornek: String sinifi](res/src/smf_copy_assign02.cpp)

> **DIKKAT!**  
> Copy assignment implement edilirken **self assignment** problemine dikkat edilmelidir.  
> Alternatif olarak [copy & swap idiom](999_kavramlar.md#copy--swap-idiom)'u kullanabilir: 
> * strong exception guarentee
> * self assignment control yapilmak zorunda kalinmiyor.

**Copy ctor'da bahsedilen durumdan kaynakli problemlere ek olarak, copy assigment default edildiginde**
1. **Resource-leak olusacaktir**: Sinif kendi kaynaklarinin uzerine yazacagi icin, dtor calistiginda kopyalamadan onceki kaynaklari release etmeyecektir!

> **DIKKAT!**  
> Tipik olarak eger bir sinifa destructor yazilmasi gerekiyor ise, copy assignment da **yazilmali**dir yada **delete** edilmelidir.


