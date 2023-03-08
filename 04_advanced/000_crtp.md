# CRTP
*Curiously recurring template pattern*

Bir taban sinifin, bir sinif sablonunu kendi acilimi ile inherit etmesidir. Boyle bir durumda, bir taban sinif kendi turemis sinifini template parametresi uzerinden kullanabilme olanagi kazanmaktadir.

```C++
template <typename T>
class Base {
public:
    void func() {
        auto* pder = static_cast<T*>(this);
        pder->foo(); // syntax hatasi degil, cunku henuz instantiate edilmedi
    }
};

class Derived : public Base<Derived> {
public:
    void foo();
};
```

Derived` sinifi, `Base<Derived>` acilimindan kalitimi yoluyla elde edildigine gore, her `Derived` nesnesi ayni zamanda bir `Base<Derived>` nesnesidir. Yani; `Base<Derived>` gereken yerde dogrudan `Derived` kullanilabilir.*  
[Ornek 1](res/src/crtp01.cpp)  

CRTP, [virtual dispatch](../01_lang/295_virtual_dispatch.md#virtual-dispatch) mekanizmasina bazi durumlarda bir alternatif olarak da kullanilabilir.  
[Ornek 2: Animals](res/src/crtp02.cpp)
  
  
* CRTP, compile-time mekanizmalarindan faydalanmaktadir, runtime maliyeti yoktur.
* Yapilacak kalitimlarda bir turemis sinif `Derived` icin taban sinifinda kendi acilimindan `Base<Derived>` yapilacagi kabul edilmektedir.  
  *Taban sinif icinde, turemis sinifin belirli bir interface'e sahip oldugu kabul edilir.*
* Turemis siniflara boilerplate kodlar ile ozellik eklemede kullanilabilmektedir.  
  [Ornek: equivalence_comparable - 1](res/src/crtp03.cpp)  
  [Ornek: equivalence_comparable - 2](res/src/crtp04.cpp)  
<!--  -->

