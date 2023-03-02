# Random Kutuphanesi
*https://pd.codechef.com/docs/cpp/cpp/numeric/random.html*

C++ rastgele sayi uretimi ile ilgili destegi saglamaktadir.

**pseudo random number generation**
sozde: Gercek bir rastgele sayi uretimi degil, deterministik
```
input => output
seed value => random number chain
```

**tru(ly) random number generation**
Dogadan kaynakli ongorulemez, non-deterministic


Neden pseudo random kullanilir?
* Maliyet
* Deterministik olmasi bazi durumlarda fayda saglayabiliyor

<!--  -->

* `random` baslik dosyasinda bulunur.
* `random` kutuphanesi kriptolojik uygulamalarda kullanim icin guvenli degildir.
* rastgele sayi uretimini saglayan nesneler bir sinif sablonudur.

C++ rastgele sayi uretimi ayni seed degeri icin ayni sayilari uretme garantisi vermektedir. Ancak dagilim siniflari ayni ciktiyi vermek zorunda degildir.
[Ornek](res/src/random01.cpp)

## Random number engines
Random number engines generate pseudo-random numbers using seed data as entropy source. Several different classes of pseudo-random number generation algorithms are implemented as templates that can be customized.

The choice of which engine to use involves a number of tradeoffs: the linear congruential engine is moderately fast and has a very small storage requirement for state. The lagged Fibonacci generators are very fast even on processors without advanced arithmetic instruction sets, at the expense of greater state storage and sometimes less desirable spectral characteristics. The Mersenne twister is slower and has greater state storage requirements but with the right parameters has the longest non-repeating sequence with the most desirable spectral characteristics (for a given definition of desirable).

Random number engines satisfy `UniformRandomBitGenerator`:

* **linear_congruential_engine** (C++11)
implements linear congruential algorithm
(class template)

* **mersenne_twister_engine** (C++11)
 implements Mersenne twister algorithm
(class template)

* **subtract_with_carry_engine** (C++11)
implements subtract with carry (a lagged Fibonacci) algorithm
(class template)

[Ornek: sizeof some random number engines](res/src/random02.cpp)

### `std::mt19937`

```C++
typedef mersenne_twister_engine<
    uint_fast32_t,
    32, 624, 397, 31,
    0x9908b0dfUL, 11,
    0xffffffffUL, 7,
    0x9d2c5680UL, 15,
    0xefc60000UL, 18, 1812433253UL> mt19937;
```

> **Not**
> The 10000th consecutive invocation of a default-contructed std::mt19937 is required to produce the value 4123659995.
> 
> The 10000th consecutive invocation of a default-contructed std::mt19937_64 is required to produce the value 9981545732273789042
> [Ornek](res/src/random03.cpp)

* Rastgele sayi uretimi `operator()` fonksiyonu ile yapilmaktadir.
* `mt19937` sinif nesnesinin boyutu **5000 byte**dir. Kopyalama yapilan yerlere dikkat edilmelidir.
  ```C++
  std::mt19937& engine()
  {
    static std::mt19937 eng;
    return eng;
  }
  ```
* Bazi STL algoritmalari rastgele sayi ureteci istemektedir. Normalde STL genel olarak copy-by-value parametreler ile calismasina ragmen bu algoritmalar **universal ref** parametrelere sahiptir. *Ornegin `shuffle` algoritmasi*

`default ctor`

`eng.seed()`

`eng.discard()`

Her URNG'in bir state'i bulunur ve `operator<<` ve `operator>>` ile [serialize/deserialize](999_kavramlar.md#serializedeserialize) edilebilir. Ayrica karsilastirma icin `operator==` overloadu bulunur.
[Ornek](res/src/random05.cpp)

`eng::min()`
`eng::max()`


### seed degerini gercek rastgele sayi yapmak
1. [std::random_device](res/src/random06.cpp)
   ```C++
   mt19937 eng{ random_device{}() };
   ```
2. [time](res/src/random07.cpp)
   ```C++
   mt19937 eng(steady_clock::now().time_since_epoch().count());
   ```

## Random number engine adaptors
Random number engine adaptors generate pseudo-random numbers using another random number engine as entropy source. They are generally used to alter the spectral characteristics of the underlying engine.

```
seed -> RNG -> Adaptor -> output
```

* **discard_block_engine** (C++11)
discards some output of a random number engine
(class template)

* **independent_bits_engine** (C++11)
packs the output of a random number engine into blocks of specified number of bits
(class template)

* **shuffle_order_engine** (C++11)
delivers the output of a random number engine in different order
(class template)



## Distribution
### Uniform Distribution
Her uretilebilecek rastgele sayinin benzer uretilme ihtimali bulunur.

```C++
template<typename _IntType = int>
class uniform_int_distribution;
```

```C++
uniform_int_distribution<> dist {min, max};     // [min, max] araliginda sayi dagilimi
mt19937 eng;

auto rand_num = dist(eng);  // dist.operator()(eng);
```
[Ornek](res/src/random08.cpp)

* Serialize/Deserialize edilebilir.
* Derleyiciler arasinda implementasyon farkliliklari bulunabilir.

`dist.param()` 
Distribution sinifinin parametrelerini belirten bir nesne dondurur.
```C++
uniform_int_distribution<int>::param_type
```

```C++
mt19937 eng;
uniform_real_distribution dist { 0., 3.14 };
```

### Normal Distribution
Her uretilebilecek rastgele sayi ortalama degere daha yakin olusma ihtimali bulunur.

```C++
template<typename _IntType = int>
class normal_distribution;
```
[text](res/src/random12.cpp)

### Bernoulli Distribution
template degil dogrudan siniftir.
[text](res/src/random13.cpp)

### Discrete Distribution
Weighted distr.
[Hileli zar ornegi](res/src/random14.cpp)


## Rastgele sayi uretimi ile ilgili algoritmalar
### `shuffle`
Bir range'i rastgele olarak tekrardan duzenler.

### `generate` / `generate_n`
Bir range'i bir generator'un urettigi degerler ile doldurur.
```C++
template <typename FwdIter, typename Fn>
void generate(FwdIter beg, FwdIter end, Fn f)
{
    while(beg != end) {
        *beg++ = f();
    }
}
```
[Ornek](res/src/generate01.cpp)
[Ornek](res/src/random19.cpp)

`entropy()`
*implementation-defined*: 
gcc 12'de 32 if /dev/random and /dev/urandom are available for std::random_device else 0.
[Ornek: entropy](res/src/random20.cpp)