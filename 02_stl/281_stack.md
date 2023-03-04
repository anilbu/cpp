## `std::stack`

The `std::stack` class is a container adaptor that gives the programmer the functionality of a stack - specifically, a LIFO (last-in, first-out) data structure.

```C++
template<typename T,
         typename Container = std::deque<T>>
class stack;
```
`Container`: The type of the underlying container to use to store the elements.  
The container must satisfy the requirements of `SequenceContainer`.  

Additionally, it must provide the following functions with the usual semantics:
* `back()`
* `push_back()`
* `pop_back()`

> :triangular_flag_on_post: 
> The standard containers `std::vector`, `std::deque` *(default)* and `std::list` satisfy these requirements.

[Ornekler](res/src/stack01.cpp)  
[Ornekler: Matching paranthesis](res/src/stack02.cpp)  
[Ornekler: Inheriting a stack](res/src/stack03.cpp)  

#### Constructors
* Default ctor
* Move ctor
* Copy ctor
* Range ctor[C++23]

> :triangular_flag_on_post: 
> Constructorlar **explicit** olarak tanimlanmistir.

> :warning: `std::initializer_list` ctor bulunmamaktadir.

#### Element Access
`top`

> :warning: stack sinifinin iterator access fonksiyonlari yoktur.

#### Capacity
`empty` `size` 

#### Modifiers
`push` `emplace` `pop` `swap` 

> :warning: 
> C++'da `pop` fonksiyonu sadece ogeyi container'dan cikarir, **geri dondurmez**.  
> &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;*Nothrow exception garantisinin saglanabilmesi icin* 
<!-- TODO: Exception garantisi ile ilgili arastir  -->

> :warning: Bos bir stack uzerinde `pop()` cagrisi yapilmasi **UB**'dir.  

<details>
<summary><b>Possible implementation</b> (Click to expand)</summary>

```C++
template <typename T, typename TContainer = std::deque<T>>
class stack 
{
public:
    void push(const T& t)
    {
        c.push_back(t);
    }
    
    void push(T&& t)
    {
        c.push_back(std::move(t));
    }
    
    size_t size() const { 
        return c.size();
    }
    
    void pop()
    {
        c.pop_back()
    }
    
    T& top() {
        return c.back();
    }
    
protected:
    TContainer c;
};
```
</details>
<!--  -->


[Ornek kod](src/39_pqueue.cpp)
