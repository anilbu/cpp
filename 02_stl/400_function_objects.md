# Function Objects
A function object is any object for which the function call operator is defined.

* Cogunlukla algoritmalara arguman olarak verebilmek icin
* Template argumani olarak kullanimi

## Function Wrappers
### `std::function` 
```C++
template<class>
class function; /* undefined */

template<typename R, typaname ...Args>
class function<R(Args...)>;
```
Class template std::function is a general-purpose polymorphic function wrapper.  

* Template parametresine karsilik gelen tur bir **fonksiyon turu** olmak zorundadir.
  > :warning: Fonksiyon turleri ile fonksiyon pointer turleri farkli turlerdir.
  > 
  > <details>
  > <summary><b>Aciklama</b> (Click to expand)</summary>
  > 
  > ```C++
  > int(int)          // -> function type
  > int(*)(int)       // -> function ptr type
  > ```
  > ```C++
  > int func(int);
  > 
  > decltype(func)  // == int(int)
  > &func           // int(*)(int)
  > ```
  > </details>
  > <!--  -->
  > 

* **Generic** bir fonksiyon sarmalayicisidir.  
  *Fonksiyon pointer turleri sadece fonksiyon adres turleri ve stateless lambda ifadeleri ile kullanilabilirken, bir `std::function` nesnesi tum callable turler ile kullanilabilmektedir.*

* C'de ve C++'da fonksiyon turlerini parametre veya geri donus turu olarak **kullanilamamaktadir**!  
  *Fonksiyon parametre turleri decay'e ugrayarak bir function pointer olur.*
  <details>
  <summary><b>Aciklama</b> (Click to expand)</summary>
  
  ```C++
  void func(int(int));    // func = void func(int(*)(int));
  void func(int(*)(int)); // redeclaration, overload degil
  ```
  ```C++
  void foo(std::function<int(int)>);
  std::function<int(int)> bar();
  ```
  </details>
  <!--  -->
  

[Ornek](res/src/function01.cpp)  
[Ornek: callback vector](res/src/function02.cpp)  

#### Member functions
`(constructor)` `(destructor)` `operator=` `swap` `operator bool` `operator()` 

* Default initialize edilebilir. Ancak, bu durumda bir callable'a sahip olmayacaktir.
  
  > :warning: 
  > Bir callable'a sahip olmayan bir `std::function` nesnesi ile cagri yapildiginda, `std::bad_function_call` turunden bir **exception throw** eder. *(Tanimsiz davranis degildir.)*

#### Target access
`target_type` `target`

### `std::mem_fn`
```C++
template< class M, class T >
/*unspecified*/ mem_fn(M T::* pm) noexcept;
```
Bir sinifin member fonksiyonu sarmalayan bir fonksiyondur. Uretilen fonksiyona bir objenin adresi de gecilebilir.

[Ornek](res/src/mem_fn01.cpp)  

## Function Invocation
### `std::invoke`/`std::invoke_r`
```C++
template< class F, class... Args >
std::invoke_result_t<F, Args...>
    invoke( F&& f, Args&&... args ) noexcept(/* ... */);
```
Generic callable invoker. Callable ve argumanlari alip perfectly forward ederek cagri yapar. Member function pointeri kullanimini kolaylastirmaktadir.

[Ornek](res/src/invoke01.cpp)  


## Partial Function Application
### `std::bind`
```C++
template<typename F, typename ...Args>
/*unspecified*/ bind(F&& f, Args&& ...args);

template<typename R, typename F, typename ...Args>
/*unspecified*/ bind(F&& f, Args&& ...args);
```
Bir callable'in interface'ini degistirmek amaciyla kullanilabilen bir sinif turunden *callable* bir nesne dondurur.

> :triangular_flag_on_post: `placeholder::` identifier'lari `bind` fonksiyonunun urettigi fonksiyonun parametrelerini *(siralariyla birlikte)* ifade etmektedir.

> :warning: Baglanan fonksiyonun parametresi bir ref turu olsa dahi, bind'in urettigi callable nesnesi degerini argumandan almasindan dolayi, cagri yapildiginda *call-by-value* gibi davranis gostermektedir. Argumanin call-by-ref olarak iletilmesi icin `ref()` ile gonderilmelidir.
> 

[Ornek 1](res/src/bind01.cpp)  
[Ornek 2: ref ile kullanim](res/src/bind02.cpp)  
[Ornek 3: greater ile kullanim](res/src/bind03.cpp)  
[Ornek 4: Functor ve lambda ile kullanim](res/src/bind04.cpp)  
[Ornek 5: Member function ile kullanim](res/src/bind05.cpp)  

## Negators
### `std::not_fn`
```C++
template< class F>
/*unspecified*/ not_fn( F&& f );
```
Bir callable sarmalar ve sarmalanan fonksiyonun geri donus degerinin logic tersini return eden bir fonksiyon ureten bir fonksiyondur.



[Ornek](res/src/not_fn01.cpp)  

## Reference Wrappers
### `std::reference_wrapper` / `ref` / `cref`
```C++
template<typename T>
class reference_wrapper;
```
A CopyConstructible and CopyAssignable wrapper around a reference to object or reference to function of type `T`. 

<!--  -->

* `<functional>` baslik dosyasinda bulunur.
* **Rebindable**: Olusturulduktan sonra bir baska nesneye tekrar baglanabiliyor. 
* Sentaks olarak ref turu kullanilamayan yerlerde bir ref kullanimina imkan sagliyor.

  > :triangular_flag_on_post: *Ref* turleri ile array olusturulamaz, containerlarda barindirilamaz. Ancak `reference_wrapper` tutulabilmektedir.

* Parametresi reference turunden olmayan fonksiyonlara reference arguman gonderebilmek icin kullanilabilmektedir.  
  * *Buyuk nesnelerin call-by-ref arguman olarak gonderilmesi*  
  * *Kopyalamaya kapali siniflari arguman olarak gonderilmesi*  

[Ornek 1](res/src/reference_wrapper01.cpp)  
[Ornek 2](res/src/reference_wrapper02.cpp)  
[Ornek 3](res/src/reference_wrapper03.cpp)  
[Ornek 4](res/src/reference_wrapper04.cpp)  
[Ornek 5](res/src/reference_wrapper05.cpp)  

#### Member Functions
`(constructors)` `operator=` `get()` `operator T&` `operator()` 

> :warning: `reference_wrapper` bir *lvalue expr* olmak zorundadir, *rvalue expr* olamaz.

#### Non-member Helper Functions
`ref()` `cref()`

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

```C++
template <typename T>
class ReferenceWrapper {
public:
    ReferenceWrapper(T& r) : mp{ &r } {}
    operator T&()   { return static_cast<T&>(*mp); }
    
    T& get() { 
      return *mp; 
    }
    
    ReferenceWrapper& operator=(T& r) { 
        mp = &r;
        return *this;
    }
    
private:
    T* mp;
};

template<typename T>
ReferenceWrapper<T> ref(T& r){
    return ReferenceWrapper<T>{r};
}
```
</details>
<!--  -->


## Operator Function Objects
**Arithmetic operations**  
`plus` `minus` `multiplies` `divides` `modulus` `negate`  
**Comparisons**  
`equal_to` `not_equal_to` `greater` `less` `greater_equal` `less_equal`  
**Logical operations**  
`logical_and` `logical_or` `logical_not`  
**Bitwise operations**  
`bit_and` `bit_or` `bit_xor` `bit_not`  

[Ornekler](res/src/operator_func_obj01.cpp)  

> :triangular_flag_on_post: Transparent function object olmalari nedeniyle template argumani belirtilmese de cikarim yapilabilmektedir. *Bu ozellik CTAD'dan farkli bir ozelliktir.*

