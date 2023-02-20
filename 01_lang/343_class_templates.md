## Class Templates
*Sinif sablonlari*

<!-- Ders 28 00:11:00 civari -->

class templatede derleyiciye class kodu yazdirmaya yonelik bir sablon turudur.

```C++
template <typename T>
class Myclass {};
```

* class template **bir sinif degildir**. class template specialization'i bir siniftir.  
  *Soz gelimi sinif denilir, ancak teknik olarak sinif degildir. Sinif olusturmayi saglayan bir koddur.*
  ```
  class template ==> instantiation ==> class (specialization)
  ```
* Ayni sinif sablonunda olusturulan specializationlarin her biri **farkli sinif turleri**dir.
  *`vector<int>` ile `vector<double>` farkli turlerden siniflardir.*

* Template argumani turu ile sinif acilimi turu karistirilmamalidir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  struct Nec{ 
      Nec() 
      {
          std::cout << "type T = " << typeid(T).name() << '\n';
          std::cout << "class type = " << typeid(Nec).name() << '\n';
      }
  };
  ```
  ```C++
  Nec<int> x1;        // T = int,      x1 = Nec<int>
  Nec<double> x2;     // T = double,   x2 = Nec<double>
  Nec<Nec<int>> x3;   // T = Nec<int>, x3 = Nec<Nec<int>>
  ```
  </details>

  <!--  -->
  
* Class definition icinde sinifin kendi ismi kullanilir ise, aslinda kullanilan sinifin specialization'ini ifade etmektedir.
  ```C++
  template <typename T>
  class Myclass {
  public:
    Myclass() = default;  // Myclass<T>() = default;
    
  private:
    T m_cnt;
  };
  ```
  ```C++
  template <typename T>
  T Counter<T>::get() const {
    return m_cnt;
  }
  ```
  [Ornek: class definition icinde `Counter` ile `Counter<T>` arasinda fark yoktur.](res/src/343_class_templates/counter01/)

* Sinifin non-static ve static fonksiyonlarin tanimi, sinif tanimi icinde de disinda da yapilabilir.
  <details>
  <summary><b>Sinif icinde</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  class Myclass {
  public:
    Myclass() = default;  // Myclass<T>() = default;
    
    void set(T val) {
      m_cnt = val;
    }
    T get() const {
      return m_cnt;
    }
  private:
    T m_cnt;
  };
  ```
  </details>
  <!--  -->
  Ancak sinif disinda yapilan tanimlamalar template olarak bildirilmek zorundadir.
  
  <details>
  <summary><b>Sinif disinda</b> (Click to expand)</summary>
  
  ```C++
  template <typename T>
  class Myclass {
  public:
    Myclass() = default;  // Myclass<T>() = default;
    
    void set(T val);
    T get() const;
  private:
    T m_cnt;
  };
  
  template <typename T>
  T Counter<T>::set(T val) {
    m_cnt = val;
  }
  
  template <typename T>
  T Counter<T>::get() const {
    return m_cnt;
  }
  ```
  </details>
  <!--  -->
  
  [Ornek: Counter sinifi](res/src/343_class_templates/counter01/)
  
  > **Hatirlatma**
  > Fonksiyonlarin geri donus turleri class scope icinde degildir.
  
  > **DIKKAT!**
  > template'ler **ODR acisindan** varsayilan olarak **inline**dir. 
  > `inline` anahtar sozcugu ile derleyiciye *inline extension yapabilirsin* bildirimi icin ayrica kullanilabilmektedir.


* Yazilan algoritmanin *-bir isin nasil yapildiginin bilgisi-* turden bagimsiz olarak yazilmasini saglar, ancak uretilen kod ture baglidir.
  
  > **Bilgi**
  > [Algoritma](https://tr.wikipedia.org/wiki/Algoritma) terimi [El-harizmi](https://tr.wikipedia.org/wiki/H%C3%A2rizm%C3%AE)'in Latince isminden gelmektedir. 

* template instantiation yapilmazsa, o sinif acilimi icin obje kodu uretilmez. Bu durum, kullanilmayan member fonksiyonlar icin de gecerlidir.
  ```C++
  std::string str{ "test" };    // sadece ctor ve dtor kodu uretilir
                                // cunku digerleri kullanilmadi!
  ```

  > **DIKKAT!**
  > Member function definition'da syntax hatasi olabilecek bir durumda eger ilgili tur ile fonksiyon kullanilmamis ise kod uretilmeyecegi icin dogal olarak sentaks hatasi da uretilmeyecektir.

* class template'ler *eger disari expose edilecek ise* **sadece baslik dosyasi**nda bulunabilir. 
  
* Bir sinif ile yapilabilen hersey class template specialization *sinif sablonu acilimi* icin de yapilabilir.
  ```C++
  Myclass<int> x;
  Myclass<int>* p { &x };   // Myclass<int> pointer
  Myclass<int>& r { x };    // Myclass<int> reference
  ```

* Fonksiyon sablonlari ile sinif sablonlari birbiri ile iliskili olabilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  bool operator==(const Myclass<int>& a, const Myclass<int>& b);
  bool operator==(const Myclass<double>& a, const Myclass<double>& b);
  ```
  Yukaridaki bildirimler yerine soyle bir bildirim de yapilabilir:
  ```C++
  template<typename T>
  bool operator==(const Myclass<T>& a, const Myclass<T>& b);
  ```
  > **DIKKAT!**
  > Yukaridaki ornekte parametreler `const Myclass<T>&` yerine `const T&` olsaydi bu tum turler icin gecerli oldurdu!
  </details>
  <!--  -->
  
* class templateler icin [C++17]'e kadar type deduction yapilamiyordu. [[bknz: CTAD](341_template_params_and_args.md#ctad-c17)]

**Ornekler ve Dikkat edilmesi gereken noktalar**

* Farkli acilimlari birlikte kullanilabilmesi icin farkli template parametreleri kullanilmalidir.
  [Ornek](res/src/class_template01.cpp)
  ```C++
  template <typename T>
  class Myclass {
      template <typename U>
      void func(Myclass<U> p);
  };
  ```

* Sinif tanimi icinde yapilan `T&&` bir rvalue reference'dir.
  *Universal reference olabilmesi icin `T&&` icin cikarim yapilmalidir!*
  [Ornek: vector sinifi](res/src/class_template02.cpp)
  ```C++
  template <typename T>
  class Myclass {
  public:
    void func(T&& x);   // x = rvalue ref
  };
  ```
  > **DIKKAT!**
  > Cikarim `T` icin class template instantiationda yapildi, fonksiyon parametresi `T&&` icin degil!
  
* Fabrika fonksiyonlari
  ```C++
  template <typename T>
  class Myclass { 
  public:
    Myclass(T x);
  };
  
  template <typename T>
  Nec<T> make_myclass(T x) {
    return Myclass<T>{x};
  }
  ```
  ```C++
  auto x = make_myclass(12);
  ```