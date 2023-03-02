# Perfect Forwarding

Kavramsal olarak perfect forwarding; bir argumanin turu, `const`lugu ve `value category`si **degismeden** iletilebilmesini saglar. Perfect forwarding yapmayi saglayan araclar C++11 ile dile eklenmistir.

## Neden Perfect Forwarding?

**Problem**
Oyle bir `call_func` fonksiyonu yazin ki, `func`'a verilen argumanlar ile yapilan cagrinin aynisi gibi *(`const`luk ve value kategorisi degismeden)* davranarak calissin.

```C++
void func(Myclass&);        // (1)
void func(const Myclass&);  // (2)
void func(Myclass&&);       // (3)

void call_func(???);
```
```C++
Myclass m;
const Myclass cm;

// (1)
func(m);
call_func(m);

// (2)
func(cm);
call_func(cm);

// (3)
func(Myclass{});
call_func(Myclass{});
```
[**Cozum 1**](res/src/perfect_forwarding01.cpp)
Her `func` overloadu icin ayri bir `call_func` overloadu yazilir.
```C++
void call_func(Myclass& x)
{
    func(x);
}

void call_func(const Myclass& x)
{
    func(x);
}

void call_func(Myclass&& x)
{
    func(std::move(x));    // x parametresi rvalue ref ancak lvalue kategorisinde
}
```
Ancak, cozum 1 ile birden fazla parametresi olan bir fonksiyona uygulanmasi gerektiginde her parametre icin benzer overloadlarin eklenmesi gerekmektedir.

[**Cozum 2**](res/src/perfect_forwarding02.cpp)
Forwarding reference *(universal referance)*  ile perfect forwarding kullanimi
```C++
template <typename T>
void call_func(T&& x)
{
    func(std::forward<T>(x));
}
```

`call_func`a lvalue expr ile cagri yapildiginda, `T` turu cikarimi `Myclass&` olarak yapilacak ve reference collapsing uygulanarak **lvalue ref parametresi** olusacaktir.
`call_func`a const lvalue expr ile cagri yapildiginda, `T` turu cikarimi `const Myclass&` olarak yapilacak ve reference collapsing uygulanarak **const lvalue ref** parametresi olusacaktir.
`call_func`a rvalue expr ile cagri yapildiginda, `T` turu cikarimi `Myclass&&` olarak yapilacak ve reference collapsing uygulanarak **rvalue ref** parametresi olusacaktir.

Kisaca, **universal reference** parametreli bir template'iniz varsa, olusturulacak specialization parametre degiskenleri ya `lvalue ref` yada `rvalue ref` olacaktir.

> :warning:   
> Universal ref bir parametreye **lvalue expr** gonderilirse `T` icin cikarim `T&` olarak yapilir, 
> ancak **rvalue expr** arguman ile cagrildiginda `T` turu icin cikarim `T` *(bir referans turu degil)* olarak yapilir. [bknz: Reference collapsing](100_ref_semantics.md#reference-collapsing)
> ```C++
> template <typename T>
> void func(T&& x)
> {
>     T a;  // rvalue expr gonderilirse gecerli, cunku T bir ref turu degil
>           // lvalue expr gonderilirse gecersiz, init edilmemis bir lvalue ref olustu.
> }
> ```

Birden fazla parametreli bir fonksiyon icin:
```C++
template <typename T, typename U, typename W>
void call_func(T&& t, U&& u, W&& w)
{
    func(std::forward<T>(t),
         std::forward<U>(u),
         std::forward<W>(w));
}
```
> :warning: 
> Aslinda `std::forward` bir nesneyi forward etmiyor, forward edilecek **deger kategorisine donusum gerceklestirmektedir**.
  <!-- std::forward fonksiyonunun detaylari ileri C++ kursunda anlatilacak. -->

**Ornek**
* `make_unique` fonksiyonu bir sinifin ctor'una perfect forwarding yapilarak cagri yapilmasini saglar.
  ```C++
  class Myclass {
  public:
    Myclass(int&, double&, float);
  };
  ```
  ```C++
  auto p = make_unique(ival, dval, 3.4f);
  ```