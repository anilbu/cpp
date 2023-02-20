#pragma once
#include <ostream>
#include <istream>

class Cint {
public:
    explicit Cint(int x = 0) : m_val{x} 
    {
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Cint& a) {
        return os << '(' << a.m_val << ')';
    }
    
    friend std::istream& operator>>(std::istream& is, Cint& a) { 
        return is >> a.m_val;
    }
    
    friend bool operator==(const Cint& a, const Cint& b) { 
        return a.m_val == b.m_val;
    }
    
    friend bool operator<(const Cint& a, const Cint& b) { 
        return a.m_val < b.m_val;
    }
    
    // unary + isaret operatoru
    Cint operator+() const {
        return *this;
    }
    // unary - isaret operatoru
    Cint operator-() const {
        return Cint{ -m_val };
    }
    
    Cint& operator+=(const Cint& a) {
        m_val += a.m_val;
        return *this;
    }
    
    Cint& operator*=(const Cint& a) {
        m_val *= a.m_val;
        return *this;
    }
    
        Cint& operator++() {
        ++m_val;
        return *this;
    }
    
    // postfix ++
    Cint operator++(int){
        Cint temp { *this };
        ++*this;   // Genel cozum: prefix ++ operatorunu kullanmak
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
        --*this;   // Genel cozum: prefix ++ operatorunu kullanmak
        return temp;
    }
    
private:
    int m_val;
};

// DIKKAT: < ve == operatorleri kullanilarak yazildi:
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

inline Cint operator+(const Cint& a, const Cint& b) {
    // Cint temp { a };
    // temp += b;
    // return temp;
    return Cint{ a } += b;
}

inline Cint& operator*(const Cint& a, const Cint& b) { 
    return Cint{ a } *= b;
}
