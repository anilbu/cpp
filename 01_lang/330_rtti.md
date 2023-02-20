# Runtime Type Information (RTTI)

<!-- Ders 27 35:40:00 - 1:52:00 -->

C++ dilinde, bir nesnenin dinamik turunun calisma zamaninda elde edilmesini saglayan bir arac setidir.

* `dynamic_cast` operatoru  
  *casting guvenli mi testi*
  ```C++
  dynamic_cast<target_type>(expr)
  ```
* `typeid` operatoru
  ```C++
  typeid(expr)
  ```

## `dynamic_cast` operatoru

Eger runtime'da [downcasting](280_inheritance.md#downcasting) basarili bir sekilde yapilabiliyorsa hedef turden bir pointer degeri donen; yapilamiyor ise `nullptr` donen bir operatordur.

**Ornek**
```C++
void func(Car* carptr)
{
    carptr->start();
    
    // Eger p bir audi tipinde ise sunroof acilacak
    // Aksi halde (p bir audi tipinde degil ise) aptr = nullptr olur.
    if(auto aptr = dynamic_cast<Audi*>(p))
    {
        aptr->open_sunroof();
    }
    
    carptr->run();
    carptr->stop();
}
```

* `dynamic_cast` operatorunun operandinin turu bir [polymorphic sinif](290_runtime_polymorphism.md#polymorphic-class) turu olmak **zorundadir**.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Base {};
  class Der : public Base {};
  ```
  ```C++
  Der der;
  Base* baseptr = &der;
  Der* derptr = dynamic_cast<Der*>(baseptr);  // syntax error: Base* bir polymorphic sinif degildir
  ```
  </details>
  <!--  -->
  

* `dynamic_cast` operatoru referans semantigi ile kullanildiginda *bir reference turune `nullptr` baglanamadigi icin* `std::bad_cast` exception throw eder.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Base {};
  class Der : public Base {};
  class Nec : public Base {};
  
  void func(Base& baseref) 
  {
    Der& dref = dynamic_cast<Der&>(baseref);
  }
  ```
  ```C++
  try{
    Der der;
    func(der);
    
    Nec nec;
    func(nec);
  }
  catch(const std::bad_cast& ex) { 
    std::cout << "ex.what() = " << ex.what() << '\n';
  }
  ```
  </details>
  <!--  -->
  

## `typeid` operatoru
```C++
const std::type_info& ti = typeid(expr)
```
* `<typeinfo>` baslik dosyasinda tanimli bulunan `std::type_info&` turunden bir nesne doner.
* `type_info` turunden bir nesne sadece `typeid` operatoru ile olusturulabilir.
* Her tur icin ayri bir `type_info` nesnesi vardir.
* Operandi polymorphic bir tur olmasi zorunlulugu yok.
* `typeid` operatorunun operandi **unevaluated context**dir.  
  **Istisna:** `nullptr` degerine sahip polymorphic bir pointer turu dereference edilir ise `std::bad_typeid` exception firlatilir. 
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  int* p = nullptr;
  Car* c = nullptr;
  
  std::cout << "sizeof(*p) = " << sizeof(*p) << '\n';
  std::cout << "typeid(*p).name() = " << typeid(*p).name() << '\n';
  try
  {
      std::cout << "typeid(*c).name() = " << typeid(*c).name() << '\n';
  }
  catch(const std::bad_typeid& e)
  {
      std::cerr << e.what() << '\n';
  }
  ```
  Output
  ```
  sizeof(*p) = 4
  typeid(*p).name() = i
  typeid(*c).name() = std::bad_typeid
  ```
  </details>
  <!--  -->
  
  
* `type_info` nesneleri karsilastirma icin kullanilabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  int x = 10;
  
  cout << typeid(int) == typeid(int) << '\n';
  cout << typeid(int) == typeid(x) << '\n';
  cout << typeid(double) == typeid(x) << '\n';
  ```
  </details>
  <!--  -->
  

* `type_info` nesnesinden tur ismi elde edilebilmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  void func(T) 
  {
      std::cout << typeid(T).name() << '\n';
  }
  ```
  ```C++
  int ar[] = {1, 3};
  func('a');          // T = char
  func(12);           // T = int
  func(ar);           // T = int*
  func("selman");     // T = const char*
  ```
  </details>
  <!--  -->
  
  > **Not**
  > Bazi derleyiciler tur isimleri [mangling](020_temel_kavramlar.md#mangling)'e ugramis hali ile donebilmektedir. Tur ismini demangle etmek icin `boost::core::demangle` fonksiyonundan faydalanabilir.
  > ```C++
  > #include <boost/core/demangle.hpp>
  > 
  > std::string typename = boost::core::demangle(typeid(int).name());
  > ```

* `typeid` operatorunun operandi polymorphic olmasi durumunda **polymorphic davranis**; olmamasi durumunda **static davranis** sergiler.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  class Base {};
  class Der : public Base {};
  
  class PolyBase {
  public:
    virtual ~PolyBase();
  };
  class PolyDer : public PolyBase {};
  ```
  ```C++  
  Der der;
  Base* p = &der;
  Base& r = der;
  auto b1 = typeid(*p) == typeid(Der);  // b1 = false, cunku polymorphic degil, static type'a bakilir
  auto b2 = typeid(r) == typeid(Der);   // b2 = false, cunku polymorphic degil, static type'a bakilir
  
  PolyDer vder;
  PolyBase* vp = &vder;
  PolyBase& vr = vder;
  auto b3 = typeid(*vp) == typeid(PolyDer);   // b3 = true, cunku polymorphic, dynamic type'a bakilir
  auto b4 = typeid(vr) == typeid(PolyDer);    // b4 = true, cunku polymorphic, dynamic type'a bakilir
  ```
  </details>
  <!--  -->

**Ornek**
Her turun kendi `type_info` nesnesi olmasi nedeniyle sadece ve sadece `Audi` turunden nesneler icin open_sunroof calisir. `AudiQ7`'nin `type_info` nesnesi farkli olmasi nedeniyle open_sunroof calismaz.
  ```C++
  void func(Car* carptr)
  {
      carptr->start();
      
      if(typeid(*carptr) == typeid(Audi))
      {
          auto aptr = static_cast<Audi*>(carptr);
          aptr->open_sunroof();
      }
      
      carptr->run();
      carptr->stop();
  }
  ```

[Ornek](res/src/typeid01.cpp)
[Ornek](res/src/typeid02.cpp)
