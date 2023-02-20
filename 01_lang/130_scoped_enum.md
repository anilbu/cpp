
-----------
**Traditional enum turleri ve problemleri**
Traditional enum syntax:
```C++
enum OldColor { CLR_RED, CLR_GREEN, CLR_BLUE };
```
1. **Underlying type**'in derleyiciye bagli olmasindan kaynakli problemler
   *C dilinde enum icin underlying type `int` turunden olmak zorunda iken C++'da ise derleyiciye bagli idi.*
   * 1 byte olarak tutulabilecek bir deger, 4 byte (int kadar) tutulmak zorunda kalinmasi.
   * incomplete type olarak kullanimi mumkun degildi.  
       enum tanimi incomplete oldugunda size'i belirlenemez ise syntax hatasi oluyor.
2. Enum turlerinden aritmetik turlere **implicit conversion** bulunmasi
3. Enum sabitlerinin bir **scope**'unun olmamasi (sabitlerin scope'u turun tanimlandigi scope'a icinde olmasi)
   ```C++
   // traffic.h
   enum traffic_light{ red, yellow, green };    // red == 0
   
   // screen.h
   enum screen_color { gray, white, red };      // red == 3
   
   int ival = red; // syntax hatasi, hangi enum turunun red sabiti?
   ```
   Bu durum icin olusturulan suni/alternatif cozumler:
   1. Enum tanimini `class` icine almak
   2. Enum tanimini `namespace` icine almak
   3. Enum sabitlerini unique tutmaya calismak
-----------

# Scoped Enum

Traditional enum turlerinde bulunan bazi problemleri gidermek amaciyla modern C++ ile dile eklenmistir. Bildirimde `class` anahtar sozcugu olmasina ragmen bir sinif turleri kategorisinin bir bileseni degildir.

```C++
enum class Color : unsigned char { RED, GREEN, BLUE };
```

* Underlying type bildirilebilmektedir.
* Sabitler, turun kendi scope'u icinde bulunmaktadir.
  ```C++
  Color mycolor = Color::RED;
  auto c1 = Color::BLUE;
  ```
  
* Aritmetik turlere implicit donusum yapilmamaktadir.
  ```C++
  Color mycolor = Color::RED;
  int x = mycolor;                      // syntax hatasi
  int y = static_cast<int>(mycolor);    // gecerli
  ```

* [C++20] Belirli bir contextde enum sabitini tur ile nitelemeden kullanilabilmesi
  ```C++
  void func1() {
    using enum Color;   // tum Color sabitleri icin
    auto c1 = RED;
  }
  
  void func2() {
    using Color::RED, Color::GREEN;   // sadece RED ve GREEN sabitini enum turu belirtilmeksizin kullanimi
    auto c1 = RED;
    auto c2 = Color::BLUE;
    auto c3 = BLUE;  // syntax hatasi
  }
  ```