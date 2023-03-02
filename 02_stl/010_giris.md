# Standard Template Library (STL)

<!-- Ders 30 1:45 STL Giris -->

STL, standard kutuphanenin buyuk bir bolumunu olusturan efficiency odakli generic bir kutuphanedir.

Runtime polymorphism cok kisitli olarak olarak kullanilmakta, genel olarak compile-time kalitim mekanizmalari kullanilmaktadir.

Exception handling cok sinirli olarak kullanilmaktadir. Cogu durumda exception firlatilmasi yerine **UB** olusmaktadir.

> **DIKKAT!**  
> Generic programlamadan kaynakli olarak sentaks hatalarinda oldukca uzun hata mesajlari uretilebilmektedir.

Containerlar, iteratorler ve algoritmalar birbiri ile dogrudan mantiksal iliski icindedir. Tasarim olarak mevcut ogeler ile uyumlu bir bicimde yeni ogeler ile genisletilebilmesine olanak saglamaktadir.

* **Iterators**  
  * **Iterator Adapters**  
* **Containers**  
  * Sequence containers  
  * Associative containers  
  * Unordered associative containers  
  * **Container Adapters**  
* **Algorithms**  
  * Non-modifying sequence operations
  * Modifying sequence operations
  * Partitioning operations
  * Sorting operations
  * Binary search operations (on sorted ranges)
  * Set operations (on sorted ranges)
  * Heap operations
  * Minimum/maximum operations
  * Comparison operations
  * Permutation operations
  * Numeric operations
  * Operations on uninitialized memory
* **Function Objects**  
  * **Function Adapters**  


## Tavsiye Kitaplar
* **The Standard C++ Library, 2nd edition**  
  N.M.Josuttis  

* [[Standard C++ IOStreams and Locales](http://www.angelikalanger.com/iostreams.html)]  
  Angelika Lenger  


> **DIKKAT!**  
> Bu dokuman STL ve standart kutuphane yapilarini ve kavramlarini cogunlukla ornekler uzerinden aciklama odakli olarak olusturulmustur, referans niteligi gostermemektedir.
