## Templateler ile ilgili Onemli Noktalar
* Kalitimdan faydalanarak **bir template base class icinde isim arama yapilabilmesi icin** `this` pointeri yada taban sinifin ismi ile **nitelenerek** kullanilmasi gerekmektedir. Normalde *(Template class olmasaydi)* legal olmasina ragmen.
  ```C++
  template <typename T>
  class Base { 
  public:
      void func();
  };
  
  template <typename T>
  class Der : public Base<T>
  {
  public: 
      void foo() {
          func();         // sentaks hatasi 
          this->func();   // gecerli
      }
  }
  ```

* Template class'dan uretilen her specialization icin ayri static veri elemani olusturulacaktir.  
  ```C++
  template <typename T>
  class Myclass { 
  public:
      static int x;
  };
  ```
  Dolayisi ile Template classdan uretilen her specialization icin static veri elemani initialize edilmelidir.
  ```C++
  // static veri elemani initialization
  template <typaname T>
  int Myclass<T>::x = 0;
  ```
  Alternatif olarak inline veri elemani[C++17] yapilabilir:
  ```C++
  template <typename T>
  class Myclass { 
  public:
      inline static int x {};
  };
  ```
  [Ornek](res/src/template_diff01.cpp)

* Bir fonksiyon sablonunun bir parametresi kodun icinde `operator()`'un operandi olursa bu ifadeyi legal yapan yapilar neler olabilir?
  ```C++
  template <typename F>
  void func(F x) 
  {
    x();
  }
  ```
  1. F bir **function pointer type** olabilir.
  2. F bir **functor class** olabilir.
  3. F bir **closure type** olabilir.

* `make_unique` tanimi ornegi:
  ```C++
  template <typename T, typename ...Args>
  std::unique_ptr<T> make_unique(Args&& ...args)
  {
      return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
  }
  ```

