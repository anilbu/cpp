## `std::priority_queue`

A priority queue is a container adaptor that provides constant time lookup of the largest (by default) element, at the expense of logarithmic insertion and extraction.

```C++
template<typename T,
         typename Container = std::vector<T>,
         typename Compare = std::less<typename Container::value_type>> 
class priority_queue;
```
`Container`: The type of the underlying container to use to store the elements.  
The container must satisfy the requirements of `SequenceContainer`, and its iterators must satisfy the requirements of `LegacyRandomAccessIterator`. 

`Compare`: 	A Compare type providing a strict *weak ordering*.

Additionally, it must provide the following functions with the usual semantics:
* `front()`  
* `push_back()`  
* `pop_back()`  

> :triangular_flag_on_post: 
> The standard containers `std::vector` *(default)* and `std::dequeu` satisfy these requirements.

[Ornekler](res/src/priority_queue01.cpp)  

#### Constructors
* Default ctor
* Move ctor
* Copy ctor
* Range ctor

> :triangular_flag_on_post: 
> Constructorlar **explicit** olarak tanimlanmistir.

> :warning: `std::initializer_list` ctor bulunmamaktadir.

#### Element Access
`top()`

> :warning: `priority_queue` sinifinin iterator access fonksiyonlari yoktur.

#### Capacity
`empty` `size` 

#### Modifiers
`push` `emplace` `pop` `swap` 

> :warning: Bos bir priority_queue uzerinde `pop()` cagrisi yapilmasi **UB**'dir.  

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

```C++

```
</details>
<!--  -->


[Ornek kod](src/39_pqueue.cpp)
