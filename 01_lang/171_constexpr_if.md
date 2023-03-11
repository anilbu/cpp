# constexpr-if[C++17]
*Static-if*

Compile-time'da verilen ifadeye gore kod blogu secimi yapilabilmesini saglayan bir aractir.

```C++
if constexpr (cond_expr) { /* ... */ }
else if constexpr (cond_expr) { /* ... */ }
else { /* ... */ }
```

* *cond_expr* bir **constexpr** ifade olmalidir ve compile-time'da degerlendirilmektedir.
* Degerlendirme sonucu secilmeyen bloklarda *dependent name*lar icin derleme yada sentaks kontrolu yapilmaz.   
  > :warning: *static_assert* degerlendirmesi *if-constexpr*'den once yapilir.

[Ornek](res/src/constexpr_if01.cpp)  
[Ornek: if-elseif merdiveni](res/src/constexpr_if02.cpp)  
[Ornek: non dependant name](res/src/constexpr_if03.cpp)  
[Ornek: advance impl. (tag-dispatch alternatifi)](res/src/constexpr_if04.cpp)  
[Ornek: auto return type](res/src/constexpr_if05.cpp)  
[Ornek: compile-time fibonnacci calculation](res/src/constexpr_if06.cpp)  
[Ornek: Variadic template](res/src/constexpr_if13.cpp)  