## `<<` ve `>>` operatorlerinin overload edilmesi

Tipik olarak I/O stream'lere giris cikis yapilmasini saglarlar.

> **Not**
> Populer olarak; `<<` operatorunu overload eden fonksiyonlara **inserter**, `>>` operatorunu overlad eden fonksiyonlara **extractor** olarak isimlendirilmektedir.

[cint.h:](res/src/00_kurslib/include/cint.h)
```C++
class Cint {
public:
    ...
    friend std::ostream& operator<<(std::ostream& os, const Cint& a) 
    {
        return os << '(' << a.m_val << ')';
    }
    
    friend std::istream& operator>>(std::istream& is, Cint& a) 
    { 
        return is >> a.m_val;
    }
    ...
};
```
[Ornek](res/src/oo01.cpp)

> **Dikkat!**  
> Yukaridaki ornekte `<<` ve `>>` operatorleri member function olarak degil, **global inline friend function** olarak bildirilmistir.

> **Not**  
> `ostream` sinifi sadece declaration'da kullanilacak ise `<iosfwd>` eklenirken; definition icin `<iostream>` baslik dosyasi eklenmelidir.
