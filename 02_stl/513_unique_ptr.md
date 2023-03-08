## `std::unique_ptr`

Tek sahiplik semantigi ile bir kaynagin hayatini yoneten sadece tasinabilen bir smart pointer'dir.

```C++
template<typename T, typename Deleter = std::default_delete<T>>
class unique_ptr;

template <typename T, typename Deleter>
class unique_ptr<T[], Deleter>;
```
`T`: Hayati kontrol edilecek tur  
`Deleter`: Kaynagin nasil sonlandirilacagini belirten tur  

* `unique_ptr`'nin `[]` turleri icin partial specialization'i bulur. 
  > :information_source: Bir partial specialization interface'i primary template'den farkli olabilmektedir.

* Tasima semantigi ile kaynagin sahibi degistirilebilmektedir.
  > :information_source: Dolu olan bir unique_ptr nesnesine tasima yapilirsa once mevcut kaynagini release eder.
  
* Incomplete type `delete` edilemeyecegi icin unique_ptr ile kullanilamaz.
  [Ornek](res/src/unique_ptr08.cpp)

* Polymorphic turler icin kullanilabilmektedir. [Ornek](res/src/unique_ptr09.cpp)  
  > :warning: Ancak [coveriance](../01_lang/295_virtual_dispatch.md#covariance) uygulanamamaktadir.


### Member Functions
`(constructor)` `(destructor)` `operator=`   

* Constructor'lari **explicit** olarak tanimlanmistir. 
* *CopyConstructor* ve *CopyAssignment* **delete** edilmistir.
* unique_ptr nesnesine atama yoluyla initialize edilebilir ancak `T` ile atama yapilamaz. *[bknz: reset()]*

> :warning: Ayni kaynak ile birden fazla `unique_ptr` initialize edilmemelidir.

[Ornek: Ctors](res/src/unique_ptr01.cpp)  

**Modifiers**  
`reset` `release` `swap`  

* `reset` fonksiyonu, verilen adresi pointer'a atar. reset'e parametresiz bir cagri yapilirsa sahibi oldugu nesnenin hayatini sonlandirir.
* `release` fonksiyonu, sarmalanan nesnenin hayatini sonlandirmadan geri doner ve pointer'i bosa cikarir.
  > :warning: release edilen kaynagin iadesi, cagiranin sorumlulugundadir.

  ```C++
  unique_ptr<Person> upx { new Myclass("obj1") };
  unique_ptr<Person> upy { upx.release() };
  ```

[Ornek](res/src/unique_ptr03.cpp)  

**Observers**  
`get` `get_deleter` `operator bool`  

* `get` fonksiyonu, sarmalanan nesnenin adresini geri doner. Nesnenin hayati sonlandirilmaz veya pointer bosa cikmaz.
  > :warning: get fonksiyonu ile unique_ptr'in kopyalanmasi **UB**'ye neden olur.
  
  > :warning: get fonksiyonu ile nesne delete edilirse, unique_ptr dangling pointer olur.

  <!--  -->

*Single-object version, unique_ptr<T>*  
`operator*` `operator->`  

*Array version, unique_ptr<T[]>*  
`operator[]`  

> :warning: Bos bir unique_ptr nesnesinin dereference edilmesi **UB**'dir.

[Ornek](res/src/unique_ptr02.cpp)  
 
### Non-member functions
`make_unique` `make_unique_for_overwrite`  
`operator==` `operator<=>`   

[Ornek: Comparison](res/src/unique_ptr12.cpp)  

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

*Partial specializations dahil degildir!*
```C++
template <typename T, typename Deleter = std::default_delete<T>>
class unique_ptr {
public:
    T& operator*() 
    {
        return *mp;
    }
    
    ~unique_ptr()
    {
        Deleter{}(mp);
    }
private:
    T* mp;
};
```
```C++
template<typename T>
struct default_delete {
  void operator()(T* p){
    delete p;
  }
};
```
```C++
template <typename T, typename ...Args>
unique_ptr<T> make_unique(Args&&... args)
{
  return unique_ptr<T>{ new T(std::forward<Args>(args)...) };
}
```
</details>
<!--  -->

-----------------

### Tipik kullanim senaryolari
* [Ornek: Dinamik omurlu kaynaklari container'larda tutulmasi](res/src/unique_ptr04.cpp)  

* [Fabrika fonksiyonlari](res/src/unique_ptr05.cpp)
  > :triangular_flag_on_post: Fabrika fonksiyonun, bir nesneyi tek sahiplik semantigi ile iletmesi, bu nesnenin tek sahiplik ilkesiyle kullanilacagi anlamina gelmemektedir. *Bir unique_ptr*, *shared_ptr*'e donusebilmektedir.

  [Sink fonksiyonlar](res/src/unique_ptr10.cpp)  
  [Pass-through fonksiyonlar](res/src/unique_ptr11.cpp)  
  
  

* [Bir sinifin veri elemanin `unique_ptr` olmasi](res/src/unique_ptr06.cpp)
  > :triangular_flag_on_post: Move-only bir veri elemani olan bir sinifin move-only olmasi dogal bir durumdur. Ancak kopyalabilir bir sinif yapilmak istenmekteyse, unique_ptr'nin tuttugu nesne deep copy yapilabilir.  
  
  > *unique_ptr* gibi move-only bir uyeye sahip bir sinif icin derleyicinin [SMF'leri implicitly declare](../01_lang/224_smf_implicit.md#smfler-icin-derleyicinin-kod-uretme-kurallari)  ettiginde, *CopyCtor* ve *CopyAssignment* **delete** edilecektir. 
  > [Ornek](res/src/unique_ptr07.cpp)

* [Pimpl idiom](res/src/unique_ptr_pimpl/)
  > :warning: *Incomplete type delete edilemez.* Sinifin dtor'u default edilecekse, `pimpl` sinifinin complete type oldugu yerde default edilmesi gerekmektedir.



  <!--  -->

--------------------------------------------------------------------------------

### `std::default_delete`
```C++
template<typename T>
struct default_delete;

template<typename T>
struct default_delete<T[]>;
```

[Ornek: Custom deleter](res/src/default_delete01.cpp)  
[Ornek: C API'leri ile kullanimi (RAII)](res/src/default_delete02.cpp)  

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

```C++
template <typename T>
struct default_delete {
    void operator()(T* p)
    {
        delete p;
    }
};

template<typename T>
struct default_delete<T[]>; {
    void operator()(T* p)
    {
        delete[] p;
    }
};
```
</details>
<!--  -->
