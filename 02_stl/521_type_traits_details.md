## Type traits - Detay

**Turler hakkinda compile-time'da bilgi edinme**  
Compile-time'da *func* fonksiyonu icin verilen `T` turu bir tam sayi turu mu kontrolu yapilmak isteniyor.  

```C++
template <typename T>
void func(T x)
{
    // T turu bir tamsayi turu mu?
}
```

*IsInteger* isimli bir template sinif olusturuldugunu varsayin.  
Bu sinifa, *value* isimli `public static constexpr bool` bir degiskenini *false* degeri ile asagidaki gibi tanimlanmis olsun:
```C++
template <typename T>
struct IsInteger {
    static constexpr bool value = false;
};
```
Bu durumda, `IsInteger<T>::value` degeri `T`'ye verilebilecek tum template argumanlari icin *false* degerinde olacaktir.

`IsInteger` template sinifina olabilecek tum tamsayi turleri icin `value` degeri *true* olacak bicimde *[explicit specialization](../01_lang/345_template_specializations.md#explicit-template-specialization)*'lar saglanmis olsa:
```C++
template <>
struct IsInteger<int> { 
    static constexpr bool value = true;
};

template <>
struct IsInteger<unsigned int> { 
    static constexpr bool value = true;
};

// ...

template <>
struct IsInteger<long int> { 
    static constexpr bool value = true;
};
```
Artik, `IsInteger<T>::value` degeri explicit specialization saglanmamis tum turler icin *false* degerinde, saglanmis turler icin *true* degerinde olacaktir.  
[Ornek: IsInteger](res/src/type_traits_detail01.cpp)

Benzer sekilde, bir turun pointer turu olup olmadiginin sinanabilmesi icin *[partial specialization](../01_lang/345_template_specializations.md#partial-template-specialization)*'lar tanimlanarak da uygulanabilmektedir.  
[Ornek: IsPointer](res/src/type_traits_detail02.cpp)

> :triangular_flag_on_post: *IsInteger*, *IsPointer* gibi siniflara **meta fonksiyon** denilmektedir.

<br/>

**Yontemin implementasyonunun kolaylastirilmasi**  
Yukarida anlatilan yontemin implementasyonunu kolaylastirmak icin soyle bir taban sinif yapilmis oldugunu varsayin:
```C++
template <typename T, T v>
struct IntegralConstant 
{
    static constexpr T value = v;
    using type = IntegralConstant;
    using value_type = T;
    
    constexpr operator value_type() const noexcept { return value; }
    constexpr value_type operator ()() const noexcept { return value; }
};
```
Artik, `IntegralConstant<int, 5>` gibi bir tur tanimi yapildiginda, `value` memberi turu `int` ve degeri `5` olan bir compile-time sabiti tanimlamasi yapilmis olacaktir.
```C++
IntegralConstant<int, 5>::value;                // = 5
IntegralConstant<int, 5>::type;                 // = IntegralConstant<int, 5>
IntegralConstant<int, 5>::value_type;           // = int
static_cast<int>(IntegralConstant<int, 5>{});   // = 5

constexpr auto val = IntegralConstant<int, 5>{} + IntegralConstant<int, 7>{};    // auto = int, val = 12
```

IntegralConstant icin `bool` turu degerleri *true* ve *false* icin tures ismi tanimlari yapilmis oldugunu varsayin:
```C++
using FalseType = IntegralConstant<bool, false>;
using TrueType = IntegralConstant<bool, true>;
```

*IsInteger* sinifi tanimlari bu turlerden kalitim yolu ile elde edebiliriz:
```C++
template <typename T>
struct IsInteger : FalseType {};

template <>
struct IsInteger<int>: TrueType {};

template <>
struct IsInteger<unsigned int>: TrueType {};

// ...

template <>
struct IsInteger<long int>: TrueType {};
```
Artik, **ortak bir arayuze** uygun olacak bicimde *meta fonksiyon*lar kolayca tanimlanabilmektedir.  

Ayrica, `_v` ve `_t` uzantili [variable template](../01_lang/344_variable_templates.md) tanimlari yapilarak daha pratik bir kullanim da saglanabilir.
```C++
template <typename T>
constexpr bool IsInteger_v = IsInteger<T>::value;

template <typename T>
constexpr bool IsInteger_t = IsInteger<T>::type;
```

[Ornek: IsInteger ve IsPointer (kalitim ile)](res/src/type_traits_detail03.cpp)  


<br/>

**Turlerin tranform edilmesi**  
Bazi meta fonksiyonlarin amaci deger hesaplamak yerine tur hesaplamasi da olabilmektedir.
Ornegin; `T` eger bir referans turu ise, referans olmayan turunu, degil ise kendi turunu kullanmak isteniyor olsun.

Yukarida aciklanan yonteme benzer sekildi bir sinifin icine `type` isimli bir alias tanimlayalim:
```C++
template <typename T>
struct RemoveReference {
    using type = T;
};
```
[template arguman deduction](../01_lang/341_template_params_and_args.md#template-argument-deduction)'dan faydalanarak asagidaki gibi specialization tanimlari yapildiginda tur cikarim `T` icin yapilmasindan dolayi `type` isimli alias turun kendisini belirtmektedir:
```C++
template <typename T>
struct RemoveReference<T&> {
    using type = T;         //  T& turleri icin type = T
};

template <typename T>
struct RemoveReference<T&&> {
    using type = T;         // T&& turleri icin type = T
};
```template <typename T>
using RemoveReference_t = typename RemoveReference<T>::type;
```
> :pushpin: Nested type'i ifade etmek icin kullanilan `typename` anahtar sozcugune dikkat edin.

[Ornek: RemoveReference type transformation](res/src/type_traits_detail06.cpp)

<br/>

**x**
Template parametresine yapilan cikarim, bir baska parametre icin'de farkli turler ile kullanilabiliyor olsun istenmektedir. Ornegin; asagida verilen func fonksiyonu icin `func(1,1)` cagrisiyla `func(1, 3.14)` cagrisi gecerli olsun istenmektedir.
```C++
template <typename T>
void func(T x, T y);
```
Yukaridaki tanima gore, hem *x* parametresi hem de *y* parametresi icin tur cikarimi yapilmakta, ancak farkli turlerden argumanlar ile cagri yapildiginda `T` cikarimi ambiguity nedeniyle yapilamayacagi icin [sentaks hatasi](../01_lang/341_template_params_and_args.md#template-argument-deduction) olusmaktadir.  

Asagidaki gibi `type` alias ile ayni turu ifade edecek bicimde bir template tanimi yapilsin:
```C++
template <typename T>
struct TypeIndentitiy {
    using type = T;
};

template <typename T>
using TypeIndentitiy_t = typename TypeIndentitiy<T>::type;
```
Fonksiyon tanimi asagidaki gibi yapildiginda ikinci parametredeki `T` icin tur cikarimi yapmak yerine ayni turu ifade edecek bicimde bir `TypeIndentitiy` instantiation'i yapilacaktir.
Bu durumda *func* fonksiyonu icin tur cikarimi sadece *x* parametresi ile yapilmaktadir. *y* parametresi ise turunu *x*'e yapilan cikarimdan alacaktir:
```C++
template <typename T>
void func(T x, TypeIdentity_t<T> y);
```
[Ornek: Type indentity](res/src/type_traits_detail07.cpp)

<br/>

**Template parametresinin belirli turler icin kisitlanmasi**  
Asagida tanimi verilen *func* fonksiyonunun sadece pointer turleri ile kullanilmasi istenmekteyse, yukarida tanimlanan *IsPointer* meta fonksiyonunun *value*'su bir compile-time sabiti olmasi nedeniyle `static_assert` ile birlite kullanabilmektedir:
```C++
template <typename T>
void func(T x)
{
    // T turu bir pointer turu degil ise sentaks hatasi versin
    static_assert(IsPointer<T>::value "T must be a pointer type");
}
```
[Ornek: Template parametresinin belirli turler icin kisitlanmasi](res/src/type_traits_detail04.cpp)

<br/>

**Turun ozelligine gore farkli iki fonksiyon implementasyonu olusturulmasi**  
Compile-time'da *func* fonksiyonu icin verilen `T` turu bir pointer ise farkli bir implementasyon, degilse baska bir implementasyon uretimi yapilmak isteniyor.  
```C++
template <typename T>
void func(T x)
{
    // T turu bir pointer turu ise bu implementasyon
    // ...
    
    // T turu bir pointer turu degil ise bu implementasyon
    // ...
}
```

*func* fonksiyonunu `func(FalseType{})` degeri ile cagrildiginda, func fonskiyonunun template parametresi `T`'nin turu `IntegralConstant<bool, false>` turunden, `func(TrueType{})` ile cagrildiginda template parametresi `T`nin turu `IntegralConstant<bool, true>` turu olacaktir.

```C++
void foo(int, TrueType);
void foo(int, FalseType);
```
> :triangular_flag_on_post: 
> *foo* fonksiyonu icin *FalseType* ve *TrueType* farkli turler olmasindan dolayi foo fonksiyonu icin function overload olusturduguna dikkat edin. *foo* fonksiyonun ikinci parametresinin turune gore hangi *foo* fonksiyonunun cagrilacagi function overload resolution ile compile-time'da tespit edilmektedir.

Benzer bicimde, *func* fonksiyonunda cagrilan *func_impl* fonksiyonunun ikinci parametresi ya bir *TrueType* turunden yada bir *FalseType* turunden olabilmektedir.
```C++
template <typename T>
void func(T x)
{
    func_impl(x, typename IsPointer<T>::type{});
}
```
Buna gore asagidaki tanimi verilen *func_impl*'ler eklendiginde, yukarida verilen ikici argumanin turune gore asagidaki implementasyonlardan biri secilecektir:
```C++
template <typename T>
void func_impl(T x, TrueType)
{
    // T turu bir pointer turu ise bu implementasyon
}

template <typename T>
void func_impl(T x, FalseType)
{
    // T turu bir pointer turu degil ise bu implementasyon
}
```
[Ornek: Ture gore kod secimi](res/src/type_traits_detail05.cpp)



