# Copy Elision
*Kopyalamanin yapilmamasi*

Bazi durumlarda sentaks geregi kodda kopyalama yada tasima yapilmasi gerekiyor olmasina ragmen, derleyicinin optimize olarak urettigi kodda kopyalamadan/tasimadan kacinmasina `copy elision` denir.

[C++17] Belirli durumlarda `copy elision` mandatory (zorunlu) hale getirildi. Daha oncesinde compiler optimizasyon teknigiydi.

> :triangular_flag_on_post: 
> Copy elision'in sadece optimizasyon teknigi olmasi ile mandatory olmasi arasindaki fark:
> 
> * Eger **sadece optimizasyon** ise derleyici bunu yapmak zorunda degil.  
>   Copy ctor cagrilamayan durumda ise (orn deleted yada private ctor) optimizasyon yapilsin yada yapilmasin, dilin kurallarina aykiri bir durum olusmasindan dolayi sentaks hatasi uretilmek zorundadir.
> 
> * Eger **mandatory** ise derleyici bu optimizasyonu yapmak zorundadir.  
>   Dilin kurallari geregi copy ctor cagrisi yapilmayacagi icin private/deleted oldugu durumlar sentaks hatasi uretilmeyecektir.

> :triangular_flag_on_post: 
> Derleyici optimizasyon flag'lari ve C++ versiyonuna gore degisebilmektedir. 

**Hangi durumlarda copy elision mandatory olarak yapilacaktir?**

* Sinif turunden parametreli fonksiyona `prvalue expr` ile cagrilirsa copy elision zorunludur.
  ```C++
  void func(Myclass)
  {
  }
  ```
  Asagidaki ifade sonucu normalde `Default ctor + Copy ctor` cagrilari yapilmasi beklenirken, copy elision sonucu sadece `Default ctor` cagrisi yapilacaktir.
  ```C++
  func(Myclass{});
  ```
  [Ornek](res/src/copy_elision01.cpp)

* Fonksiyonun geri donus turu bir sinif turunden ise ve fonksiyon bir gecici nesne ifadesi geri donduruyorsa, fonksiyon cagrisi sonucunda copy elision zorunludur.
  Buna `Return Value Optimization (RVO)` da denir.
  ```C++
  Myclass func() {
    return Myclass{};
  }
  ```
  Asagidaki ifade sonucu normalde `Default ctor + Copy ctor` cagrilari yapilmasi beklenirken, copy elision sonucu sadece `Default ctor` cagrisi yapilacaktir.
  
  Cunku `Myclass{}` return ifadesi kopyalanarak `m` degiskenine atanmak yerine dogrudan `m` degiskeninin oldugu yerde hayata getirilmektedir.
  ```C++
  Myclass m = func();
  ```

* `Named Return Value Optimization (NRVO)` fonksiyon icerisinde bulunan bir yerel sinif nesnesinin geri donulmesidir. NRVO optimizasyonu mandatory olmamasi nedeniyle dilin kurallarina gore copy ctor cagrilabiliyor durumda olmasi zorunludur.
  ```C++
  Myclass func()
  {
    Myclass ret;
  
    // buradaki kodlar ret nesnesini kullaniyor olabilir
  
    return ret;
  }
  ```
  ```C++
  auto x = func();  // ret nesnesi x'in oldugu yerde olusturulacak.
  ```
  
* **C++17'den once** Olusturulmasi maliyetli nesnelerin geri dondurulmesi icin pass by reference out parametre olarak iletirilirdi.
  ```C++
  void func(std::string& out);   // out param
  ```
  ```C++
  std::string result;
  func(result);
  ```