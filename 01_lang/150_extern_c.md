# `extern "C"`

C dilinde fonksiyon sembol isimleri overloading olmamasi nedeniyle C++'dan farklidir. Bu nedenle c dilinde derlenmis bir objeyi c++ dilinde kullanabilmek icin `extern "C"` anahtar kelimesini kullanir.

Bir fonksiyon cagrisi yapildigi zaman, eger bir inline extension soz konusu degilse (yada derleyici kodu gormuyor ise), derleyici programin akisinin fonksiyona gecmesini saglayan giris ve cikis kodlarini uretir.

Fonksiyon kodunun derlenmis halini birlestirmek **linker** programinin gorevidir. Derleyiciler, linker'in fonksiyon cagrisindaki fonksiyonun objesi ile cagiran kodun objesini birlestirebilmesi icin **object code**a bir referans yazmaktadirlar. Linker ile compiler arasinda bu referansin isimlendirmesi konusunda bir notasyon bulunmaktadir. Bu notasyona gore fonksiyon ismi dekore (name mangling) edilir. Bu isimlere **external reference** denilmektedir.

C derleyicileri ile C++ derleyicilerinin dekorasyon notasyonu arasinda ciddi bir farklilik bulunmaktadir. C dilinde ayni fonksiyon isminden birden fazla olamayacagi icin sadece fonksiyon isminden faydalanilmakta iken C++ dilinde function overloading nedeniyle mangling'de parametreleri de kullanmaktadir.


[Ornek](res/src/150_extern_c/)
module.h:
```C++
#pragma once

int func(int);
```
module.c:
```C++

#include "module.h"

int func(int x)
{
    return x * x;
}
```
main.cpp:
```C++
#include <iostream>
#include "module.h"

int main() 
{
    auto x = func(20);
    std::cout << "x = " << x << '\n';
    
}
```

> Hata: external symbol "int func(int)" referenced in function main

Yukarida olusan hatanin sebebi, derleyici func fonksiyonunun bir C fonksiyonu oldugunu bilmedigi icin C++ mangling kurallarina gore obje kodun icinde ariyor olmasidir. 

Hatanin giderilebilmesi icin C++ kodu icinde kullanilan C kodunun bir C derleyici ile derlendigini bildirilmesi gerekmektedir. C++ bu islemin yapilabilmesi icin `extern "C"` aracina sahiptir.

Syntax
```C++
extern "C" <declaration>
```
```C++
extern "C" {
    <declarations>
}
```


main.cpp:
```C++
extern "C" {
#include "module.h"
} 
```

Eger module.h hem C dilinde hemde C++ dilinde kullanilabilir olmasi icin **conditinal compiling** yapilabilir. [[bknz: Predefined symbol constants](extras/predefined_symbol_const.md)]

module.h:
```C++
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int func(int);

#ifdef __cplusplus
}
#endif
```


