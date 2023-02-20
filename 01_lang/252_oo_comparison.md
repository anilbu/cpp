## Karsilastirma operatorlerinin overload edilmesi

* 6 tane karsilastirma operatoru `==`, `!=`, `<`, `>`, `<=`, `>=`
* `binary` operatorlerdir, simetrik oldugu icin tercihen global function olarak yazilmaktadir.
* Tipik olarak return degerleri `bool` olmalidir.

* `==` ve `<` overload edilir, diger karsilastirma operatorlerinde de bu fonksiyonlara cagri yapilarak implement edilir.

> **spaceship `<=>` (three-way comparison operator) [C++20]**  
> Ileri bir derste anlatilacak.

* [C++20] `==` overload edilmis ise `!=` de otomatik olarak default edilerek overload edilir.

[cint.h:](res/src/00_kurslib/include/cint.h)
```C++
class Cint {
public:
    ...
    friend bool operator==(const Cint& a, const Cint& b) { 
        return a.m_val == b.m_val;
    }
    
    friend bool operator<(const Cint& a, const Cint& b) { 
        return a.m_val < b.m_val;
    }
    ...
};

inline bool operator!=(const Cint& a, const Cint& b) { 
    return !(a == b);
}

inline bool operator>(const Cint& a, const Cint& b) { 
    return b < a;
}

inline bool operator>=(const Cint& a, const Cint& b) { 
    return !(a < b);
}

inline bool operator<=(const Cint& a, const Cint& b) { 
    return !(b < a);
}
```

> **std::boolalpha**  
> `1` ve `0` degerlerini `true` ve `false` olarak stream'e yazdiran bir stream manipulatorudur.