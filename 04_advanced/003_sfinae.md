# SFINAE
*Substitution Failure Is Not An Error*  

> :triangular_flag_on_post: 
> *(Kullanim alanlarinin buyuk cogunlugunda artik concepts kullanilabiliyor)*

**Substitution Error**  
Bir overloading soz konusu oldugu zaman, eger overloadinge giren fonksiyonlardan biri yada birden fazlasi template ise overload set'e giren template'in kendisi degil specializationlaridir.  
*(Template argumanlari belirlenmis ve instantiation yapilacak)*  
```C++
template <typename T>
typename T::Nec func(T x);      // (1)

template <typename T>
void func(T* x);                // (2)
```
```C++
int ival{};
func(&ival);
```
*func<int*>* cagrisi sonucu olusacak fonksiyon imzalari sirasiyla:
```C++
int*::Nec func<int*>(int* x);    // (3)
void func<int>(int* x);         // (4)
```
Cagri sonucu uretilecek olan *func* fonksiyonlarindan (3)'de `int*` turunun *Nec* turunden nested type olma ihtimali olmamasina ragmen instantiate edilirken dilin kurallari geregi sentaks hatasi uretilmemektedir. Cunku, substitution asamasinda turlere yonelik hatalar, hard-error yerine overload set'e dahil etmemektedir.


[Ornek](res/src/sfinae01.cpp)  
[Ornek](res/src/sfinae02.cpp)  

## `std::enable_if`

```C++
template <bool B, typename T = void>
struct enable_if {};

template<typename T>
struct enable_if<true, T> {
    using type = T;
};

template<bool B, typename T = void>
using enable_if_t = typename enable_if<B, T>::type;
```
Kisaca, eger *B* parametresi *true* oldugu zaman, enable_if'in bir *type* isimli bir tures ismi olusmaktadir. Aksi halde tures isim bildirimi yapilmamaktadir.  
```C++
enable_if<false, int>::type var1;    // sentaks hatasi: primary template'de type bildirimi yok
enable_if<true, int>::type var2;     // var2 = int
```
Bu yapi, bir fonksiyon bildiriminde kullanildiginda *SFINAE*'den faydalanilarak fonksiyon secimi yada tur kisitlamasi amaciyla kullanilabilmektedir.  

**Ornekler**  
1. *func* fonksiyonu sadece tamsayi parametreler ile cagrilabilsin:
   ```C++
   template<typename T>
   enable_if_t<is_integral_v<T>> func(T x) {
       // ...
   }
   ```

2. *func* fonksiyonu gercek sayi turlerinde *long double* parametreli, diger turlerde templateden kod uretilsin:
   ```C++
   template<typename T>
   enable_if_t<is_integral_v<T>> func(T x) {
       // ...
   }
   
   void func(long double);
   ```
   *func(1.2)* cagrisi icin normalde template'den *double* turu icin kod uretilmesi gerekmekteyken, template fonksiyonunun *sfinaed-out* olmasi nedeniyle arguman cast edilerek *func(long double)* fonksiyonuna cagrisi yapilacaktir.

