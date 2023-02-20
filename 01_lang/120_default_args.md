# Function Default Arguments

Bir fonksiyona yapilan cagrilarda cogunlukla bir parametreleye ayni degerler gonderiliyor olabilir. Bu durumlarda parametreye varsayilan bir deger atanmasi icin **default argument** mekanizmasi kullanilabilir.

Deger gonderilemeyen parametreler icin varsayilan deger atanmasini saglar.

```C++
void func(int, int, int = 10);
```
```C++
func(10, 20, 30);
func(10, 20);
```

* Ilk verilen default arg'dan sonraki tum parametreler default degere sahip olmalidir.
  *Varsayilan argumanlar parametre listesinde **sonda olmali**dir.*
* Varsayilan deger bildirimin yapildigi yerde gorunur bir varlik olabilir.
* Parametre degiskenleri varsayilan arguman olarak kullanilamaz.
  ```C++
  void func(int x, int y = x);  // gecersiz
  ```
* Varsayilan arguman hem bildirimde hem tanimda yer almasi syntax hatasidir. 
  Ancak birden fazla bildirimde farkli parametreler icin bulunabilir.
* Varsayilan argumanlar derleyici tarafindan kumulatif olarak degerlendirilir. Fakat ayni parametreye ikici bir default arg. verilmemelidir. *Bu nedenle baska bir modulden elde edilen fonksiyona varsayilan arguman verilebilir.*
  *my_header.h:*
  ```C++
  void func(int, int, int = 10);
  ```
  *my_header.cpp:*
  ```C++
  #include "my_header.h"

  void func(int, int = 5, int); // tekrar bildirim
  
  func(1);    // func(1, 5, 10) olarak degerlendirilir.
  ```
* Hesaplama gerektiren varsayilan argumanlar her fonksiyon cagrisinda tekrardan degiskene atanir.
  [Ornek](res/src/default_args01.cpp)
  
* Varsayilan arguman gonderildi mi diye sinamak icin kullanilamayacak bir deger ile varsayilan deger verilebilir. 
  [Ornek](res/src/default_args02.cpp)
