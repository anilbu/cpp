# Generic Programming - Templates
*template/meta-code*

C++ dilinde derleyiciye kod urettirilmesini saglayan bir arac setidir.

**Template Kategorileri**

* function template
* class template
* variable template [C++11]
* alias template [C++11]
* concepts [C++20]

**Avantajlari**

* Fonksiyonlarin onemli bir kismi algoritmalari implemente ediyor ve algoritmalar genellikle ture bagli degillerdir.
  1. Tur bilinmeden isin gerceklestirilmesi (`void*`)
     ```C++
     void gswap(void* vpx, void* vpy, size_t sz);
     ```
  2. Kalitima dayali ortak bir tur kullanimi (Tum turler `Object` turunden turemis gibi)
     ```C++
     // C++ dilinde karsiligi yok
     ```
  3. Sablonlar araciligi ile kod uretiminden faydalanarak

* Cagrilmayan fonksiyonlar icin kod uretilmemesi
  *Kod uretilmez ise syntax hatasi da olusmamaktadir.*
* Kullanilan turlerin kisitlanabilmesi

<!--  -->

## Tanimlar

**template parameter and arguments**  
Derleyicinin uretecegi kodda bazi varliklara karsilik gelen parametrelere **template parameter** denir. Bu parametreler karsilik gelen argumanlara **template argument** denir.

**template parameter categories**  
1. **type parameter** *(tur parametresi)*
2. **non-type parameter**  *(sabit parametresi)*
3. **template parameter**

**template instantiation and specialization**
Bir işlev, sınıf veya sınıfın üyesi için bir şablon bildiriminden kod uretme işlemine **template instantiation** denir.

* Derleyicinin bir sablondan bir kod uretebilmesi icin sablon kodunu gormesi gerekmesinden dolayi tipik olarak **header** dosyasina eklenir. Yine de ayni kaynak dosyada bir sablon tanimi bir kere yapilabilir.

Belirli bir şablon icin belirli template argumanlarina karsilik gelecek bicimde  template instantiation sonucu derleyicinin olusturdugu sinifa **specialization** *(acilim)* denir. 
  ```C++
  std::list      // std::list isimli template'in kendisi
  std::list<int> // std::list'in int acilimi
                 //   std::list templateinin int turu icin instantiation edilmesi sonucu olusturulmus bir sinif
  ```
  * explicit specialization (full-spec)
  * partial specialization




<!-- 
-----
```C++
template <typename T>
void func(T x)
{
  std::cout << "func<" << typeid(T).name() << ">("<< x << ")\n";
}

template <typename T>
void func(T x, T y)
{
  std::cout << "func<" << typeid(T).name() << ">("<< x <<", " << y << ")\n";
}

func(12);
```
-----
 -->
