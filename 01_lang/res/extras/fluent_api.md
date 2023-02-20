**Chaining / Fluent API**  

```C++
class Myclass {
public:
    // Ref version
    Myclass& f1() { cout << "Myclass::f1() this = " << this << '\n'; return *this; }
    Myclass& f2() { cout << "Myclass::f2() this = " << this << '\n'; return *this; }
    Myclass& f3() { cout << "Myclass::f3() this = " << this << '\n'; return *this; }
    Myclass& f4() { cout << "Myclass::f4() this = " << this << '\n'; return *this; }
      
    // pointer version
    Myclass* g1() { cout << "Myclass::g1() this = " << this << '\n'; return this; }
    Myclass* g2() { cout << "Myclass::g2() this = " << this << '\n'; return this; }
    Myclass* g3() { cout << "Myclass::g3() this = " << this << '\n'; return this; }
    Myclass* g4() { cout << "Myclass::g4() this = " << this << '\n'; return this; }
}

int main(int, const char*[])
{
    Myclass m;
    m.f1().f2().f3().f4();

    Myclass* p = &m;
    p->f1()->f2()->f3()->f4();
}
```

