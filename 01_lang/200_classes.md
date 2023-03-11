# Classes - I
Problem domainindeki varliklarin programlama dilinde yazilimsal olarak ifade edilmesine data abstraction denilmektedir. Class'lar, C++ dilinde data abstraction konusunda temel aractir. 

**class declaration/forward declaration**
```C++
class Myclass;
```
Derleyiciye bir ismin sinifa oldugunu ve baska bir yerde tanimlandiginin bildirimidir.

**class definition**
```C++
class Myclass {
    // class members
};
```
Bir siinifin detaylarinin tanimlanmasidir.
* Sinif tanimlamalari ODR'a uymak zorunda. Ancak, token-by-token ayni olmasi ODR'i ihlal etmemektedir.
  *Yani, tanim birebir ayni oldugu surece header dosyasinda tanimlanip, birden fazla kaynak dosyada derlenebilir.*
* Memberi bulunmayan bir **empty class**in, `sizeof` degeri 1'dir.
* `class` yerine `struct` anahtar sozcugu ile de sinif tanimi yapilabilmektedir.
  > :warning: 
  > C'deki struct'lar C++'da bulunan `struct` ile ayni degil!

[bknz: Scopes](050_basics.md#scope)

Bir sinif turunden degiskene object (instance) denir. Her objenin kendi state'i bulunur.
```C++
Myclass x;
```

Class'a ait bir ifade uzerinde surecler su sirada gerceklesir:
1. **name lookup**
2. **context control**
3. **access control** 


## Name Lookup 
Bir isim su durumlarda class definition icinde aranir:
* Member selection (dot) operatorunun operandi ise: `obj.x`
* Arrow (ok) operatorunun operandi ise: `ptr->x`
* Scope resolution (`::`) operatorunun operandi ise: `Myclass::x`


## Access Control and Specifiers
Class taniminda erisim kontrolu belirtme amaci ile kullanilir.

* `private`: Sadece sinifin kendi kodlarinin kullanimi ile kisitlanmis kisimdir.
* `protected`: Sinifin kendi kodlari ve bu siniftan turetilen siniflarin siniflarin erisimi ile kisitlanmis kisimdir.
* `public`: Erisim kisitlamasi olmayan uyelerin bulundugu kisimdir.

> :warning: 
> Sinifin `public`, `private`, `protected` bolumleri ayri scopelar degildir.

Bir sinif `class` tagi ile tanimlanmis ise default access **private**, `struct` tagi ile tanimlanmis ise default access **public**'dir.

**Veri elemanlarinda access control olmasaydi?** 
Genel olarak sinifin isleyis detaylari disaridan gizlenerek, soyutlamaya yonelik bir arayuz verilmesi iyi bir pratiktir. [[bnkz: data-hiding](https://en.wikipedia.org/wiki/Information_hiding)]
* Bir degerin nasil kullanilacaginin kurallari disari acik birakilmis olmasi, hatali kullanimlara olanak saglamaktadir.
* Kullanici acisindan ozel durumlara ait ogrenme yukunu arttiriyor.

**Ornek**
```C++
class Myclass { 
public:
  void foo();
private:
  int x;
};
```
Asagidaki ifadelerin 
```C++
Myclass::foo(); // name-lookup gecerli, ancak context control hatasi
```
```C++
Myclass m;
foo(&m);    // name-lookup hatasi
```
```C++
Myclass::foo(&m);   // sentaks hatasi, dilin kurallarinda boyle bir cagrim yok.
```

> :triangular_flag_on_post: 
> Sinifin veri elemanlari arasinda padding olabilir, ancak bildirilen sira ile olmak zorunda degildir.


<!-- ------------------------------- -->

## Class Members

Bir sinifin memberlari sunlardan biri olabilir:
* [non-static data member](201_class_nonstatic_members.md#non-static-data-members)
* [non-static member function](201_class_nonstatic_members.md#non-static-member-function)
* [static data member](202_class_static_members.md#static-data-members)
* [static member function](202_class_static_members.md#static-member-functions)
* [type member](203_class_type_member.md#nested-types)