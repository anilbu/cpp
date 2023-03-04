## `std::array`
*static contiguous array*

[C++11] ile `<array>` baslik dosyasi ile eklendi, oncesinde `boost::array` kullanilabilir.

:heavy_check_mark:  overhead-free random access  
:heavy_check_mark:  fast traversal; good for linear searches  
:heavy_minus_sign:  size has to be a constant expression (= known at compile time)  
:heavy_minus_sign:  does not support size-changing operations (resize, insert, erase, …)  
:x:  potentially slow if element type has high copy/assignment cost  
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*(reordering elements requires copying/moving them)*  

```C++
template<typename T, std::size_t N> 
struct array;
```

> :warning: `T` turunun default constructable olmasi zorunludur.


### std::array vs raw array 
**std::array Avantajlari**  
* Raw arraylere kiyasla runtime maliyeti yoktur.
* Bir container interface'i kazandirilarak STL ile daha uyumlu hale getirilmis olmasi
* Bir container ogesi olarak dizi turu kullanilamaz, ancak `std::array` kullanilabilir.
* Bir fonksiyon dizi turu parametresi yada geri donus turu olamaz, ancak `std::array` olabilir.
* Boyutu sifir olan bir dizi olamaz ancak `std::array` olabilir
* Raw array'de array decay soz konusudur.

**Raw Array Avantajlari**  
* Raw arrayler copy-by-value atamalari mumkun degildir, ancak `std::array` bir aggregate type olmasi nedeniyle kopyalanabilirler.

<!--  -->

[Ornek](res/src/array01.cpp)

### Constructors
Aggregate initialization kurallarina uygun olarak initialize edilir. `std::array` olusturulduktan sonra boyutu degistirilemez.

> :triangular_flag_on_post: 
> Bu bir `std::initializer_list` ctor degil, *[aggregate initialization](../01_lang/050_basics.md#aggregate-initialization)*'dir.

> :warning: 
> Initialize edilmemis bir `std::array`'in kullanimi **UB**'dir.

Tasima ve kopyalamayi desteklemektedir.

### Iterators
`begin()` `end()`  `cbegin()` `cend()`  `rbegin()` `rend()`  `crbegin()` `crend()` 

### Element Access
`at` `operator[]` `front()` `back()` `data()` 

### Capacity
`empty()` `size()` `max_size()` 

### Operations
#### `fill`
#### `swap`





