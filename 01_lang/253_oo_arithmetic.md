## Aritmetik operatorlerin overload edilmesi

### `+` ve `-` isaret operatorleri
* `+x` ifadesi prvalue expressiondir. Bu nedenle geri donus turu `T&` olmamalidir.

[cint.h:](res/src/00_kurslib/include/cint.h)
```C++
class Cint {
public:
    ...
    Cint operator+() const
    {
        return *this;
    }
    Cint operator-() const
    {
        return Cint{ -m_val };
    }
    ...
};
```

### `+`, `-`, `*`, `/`, `+=`, `-=`, `*=`, `/=` operatorleri

* Tipik olarak `+=` operatoru overload edilir, `+` operatoru bu operatoru kullanarak implement edilir.

[cint.h:](res/src/00_kurslib/include/cint.h)
```C++
class Cint {
public:
    ...
    Cint& operator+=(const Cint& rhs) 
    {
        m_val += rhs.m_val;
        return *this;
    }
    
    Cint& operator*=(const Cint& rhs) {
        m_val *= rhs.m_val;
        return *this;
    }
    ...
};

inline Cint operator+(const Cint& lhs, const Cint& rhs) {
    // Cint temp { lhs };
    // temp += rhs;
    // return temp;
    return Cint{ lhs } += rhs;
}

inline Cint operator*(const Cint& a, const Cint& b) { 
    return Cint{ a } *= b;
}

inline Cint& operator-=(const Cint& lhs, const Cint& rhs) {
    return *this += -rhs;
}

inline Cint operator-(const Cint& lhs, const Cint& rhs) {
    return Cint{ m_val } -= rhs;
}

```

### `++` ve `--` operatorleri

* `++` ve `--` operatorleri prefix veya postfix olarak kullanilabilir.  
  *Bu nedenle overload edilirken ozel bir kurala tabidirler.*

`++x` ile `x++` arasindaki farklar:
1. Uretilen deger.  
   * `++x` operatoru, nesnenin degerinin bir fazlasini uretir.
   * `x++` operatoru, nesnenin kendi degerini uretir.

2. Value kategori.
   * `++x` ifadesi lvalue expressiondir.  
     Bu nedenle `++x` geri donus turu `T&` turunden olmalidir.
     
   * `x++` ifadesi prvalue expressiondir.  
     Bu nedenle `x++` geri donus turu `T` turunden olmalidir.

3. Operator fonksiyon imzalari.
   * `++x` operatoru, bir parametreye sahip degildir.  
     `T& operator++()`
     
   * `x++` operatoru, dummy bir `int` parametreye sahiptir.  
     `T operator++(int)`

* Member veya global fonksiyon olarak overload edilebilir.

[cint.h:](res/src/00_kurslib/include/cint.h)
```C++
class Cint {
public:
    ...
    // prefix ++
    Cint& operator++() {
        ++m_val;
        return *this;
    }
    
    // postfix ++
    Cint operator++(int){
        Cint temp { *this };
        ++*this;   // [prefix] operator++() cagrilarak tum siniflara uygulanabilir.
        return temp;
    }
    
    // prefix --
    Cint& operator--() {
        --m_val;
        return *this;
    }
    
    // postfix --
    Cint operator--(int){
        Cint temp { *this };
        --*this;   // [prefix] operator--() cagrilarak tum siniflara uygulanabilir.
        return temp;
    }
    ...
};
```
