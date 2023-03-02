## Karsilastirma operatorlerinin overload edilmesi

* 6 tane karsilastirma operatoru `==`, `!=`, `<`, `>`, `<=`, `>=`
* `binary` operatorlerdir, simetrik oldugu icin tercihen global function olarak yazilmaktadir.
* Tipik olarak return degerleri `bool` olmalidir.

* `==` ve `<` overload edilir, diger karsilastirma operatorlerinde de bu fonksiyonlara cagri yapilarak implement edilir.

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

### `operator==` degisiklikleri [C++20]

**Rewritable** 
Derleyici asagida aciklanan durumlar ile karsilastiginda ifadeyi tekrardan olusturabilmesini belirtmektedir.

```C++
class Myclass {
public:
    Myclass(int);
    bool operator==(const Myclass&) const;
};
```

* [C++17]'e kadar sadece SMF'lar derleyici tarafindan default edilmekteydi.  
  [C++20] ile `operator==` overloadu bulunuyor ise derleyici `operator!=`'i default etmektedir.

  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  **[C++17] ve oncesinde:**  
  ```C++
  Myclass x, y;
  auto result1 = x == y;   // gecerli
  auto result2 = x != y;   // sentaks error
  ```
  **[C++20] ile:**  
  ```C++
  Myclass x, y;
  auto result1 = x == y;   // gecerli
  auto result2 = x != y;   // gecerli
  ```
  </details>
  <!--  -->
  
* [C++20] operandlarin yer degistirebilmesi eklendi.  
  Derleyici `operator==` fonskiyonunda operandlarin uygun olmamasi durumunda yerlerini degistirerek de gecerliligini sinamaktadir.
   
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  **[C++17] ve oncesinde:**
  ```C++
  Myclass x(12), y(34);
  auto result1 = x == 90;   // gecerli: x.operator(Myclass(90));
  auto result2 = 45 == x;   // sentaks hatasi
  ```
  **[C++20] ile:**
  ```C++
  Myclass x(12), y(34);
  auto result1 = x == 90;   // gecerli: x.operator(Myclass(90));
  auto result2 = 45 == x;   // gecerli: x == 45
  ```
  </details>
  <!--  -->
  
### Three-way comparison operator[C++20]
*spaceship operator*  

```C++
int x = 10, y = 20;
x <=> y;
```

> :pushpin: 
> `strcmp(a, b)` fonksiyonunun geri donus degeri eger;
> * `a > b` ise donus degeri **sifirdan kucuk**
> * `a < b` ise donus degeri **sifirdan buyuk**
> * `a == b` ise donus degeri **sifir**dir.

Bazi turlerde karsilastirilma yapilamayan degerler bulunabilmektedir. Bazende esitlik *(equality)* ile esdegerlik *(equivalence)* birbiri ile ayni kavramlar olmayabilir.

*Ornegin case-insensitive string degerlerin karsilastirilmasi yapilirken `"masa"` ile `"MASA"` ifadeleri birbirine esit olmadigi halde denk olabilmektedir.*

`operator<=>`'unun benzer durumlara da uygunluk saglayabilmesi icin urettigi degerler asagidaki gibidir:

**strong_ordering**  
Karsilastirma sonucunda *esitlik*, *buyukluk* yada *kucukluk* ifade edilebilebiliyor ise
* `strong_ordering::less` = *-1*
* `strong_ordering::equal` = *0*
* `strong_ordering::equivalent` = *0*
* `strong_ordering::greater` = *1*

**weak_ordering**  
*Relational* karsilastirma veya *equivalance* karsilastirmasi soz konusu oldugunda kullanilmak uzere
* `weak_ordering::less` = *-1*
* `weak_ordering::equivalent` = *0*
* `weak_ordering::greater` = *1*

**partial_ordering**  
Butun degerler birbiri ile *karsilastirilabilir olmadigi* durumlarda kullanilmak uzere
* `partial_ordering::less` = *-1*
* `partial_ordering::equivalent` = *0*
* `partial_ordering::greater` = *1*
* `partial_ordering::unordered` = *2*

[Ornek](res/src/oo03.cpp)

```C++
class Myclass {
public:
    auto operator<=>(const Myclass&) const = default;
};
```
`Myclass` turunden `m1` ve `m2` nesnesi `m1 < m2` ifadesi ile karsilastirildiginda; derleyici bu ifadeyi `operator<=>`'e donusturmekte ve gerekirse operandlarin yerini de degistirebilmektedir:
```
(x <=> y) < 0
0 < (x <=> y)
```

* `operator<=>` *rewritable* bir operatordur.
* `operator<=>` default edilebiliyor.
  * Birden fazla member bulunan siniflarda, `operator<=>` default edildiginde bildirim sirasina gore karsilastirmalar yapilacaktir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  `operator<=>` default edilmesi halinde derleyicinin yazacagi kod asagidaki gibi olacaktir:
  ```C++
  class Myclass {
  public:
    // auto operator<=>(const Myclass& other) const = default;
    auto operator<=>(const Myclass& other) const 
    {
      if(auto result = m_str <=> other.m_str; result != 0)
        return result;
        
      if(auto result = x <=> other.x; result != 0)
        return result;
        
      return y <=> other.y;
    }
      
  private:
      std::string m_str;
      int x, y;
  };
  ```
  </details>
  <!--  -->
* `operator<=>` default edildiginde `operator==`'de default edilmektedir.
  Eger `operator<=>` user-declared olsaydi, `operator==` default edilmemektedir.


[Ornek: C++17 ile operator overloading](res/src/oo02.cpp)    
[Ornek: C++20 ile operator overloading (defaulted)](res/src/oo04.cpp)    
[Ornek: C++20 ile operator overloading (user-declared)](res/src/oo05.cpp)    