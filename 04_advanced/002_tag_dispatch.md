# tag dispatch

Compile-time'da elde edilen tur bilgisine gore bir fonksiyona arguman verilerek, bir overload secimini yaptirmaktadir.

Tag-dispatch'in genel felsefesi, belirli tur kategorilerinin belirli turlere sahip olmasina dayanmaktadir.

**Ornek**: [Farkli iterator kategorilerine gore *uygun implementasyon secimi* yapilmasi](res/src/tag_dispatch01.cpp)  

<details>
<summary><b>Aciklama</b> (Click to expand)</summary>

Asagida verilen Distance fonksiyonu implementasyonuna gore *RandIter* kategorisinde daha verimli bir implementasyon yapilabilme olanagi bulunmasina ragmen kullanilamayacaktir.
```C++
template <typename Iter>
int Distance(Iter x, Iter y)
{
    int cnt{};
    while(beg != end)
    {
        ++beg;
        ++cnt;
    }
    
    return cnt;
}
```
Bunun yerine farkli implementasyonlarin *iterator_tag*'ine gore secim yapilacagi farkli overloadlari olusturulsun: 
```C++
template <typename Iter>
int Distance_impl(Iter beg, Iter end, std::input_iterator_tag)
{
    int cnt{};
    while(beg != end)
    {
        ++beg;
        ++cnt;
    }
    
    return cnt;
}

template <typename Iter>
int Distance_impl(Iter beg, Iter end, std::random_access_iterator_tag)
{
    return y - x;
}
```

Distance fonksiyonunda, *Iter*'e yapilan cikarima gore uygun overload'un cagrilmasi saglanabilir:
```C++
template <typename Iter>
int Distance(Iter x, Iter y)
{
    Distance_impl(beg, end, typename Iter::iterator_category{});
}
```
Ancak, `typename Iter::iterator_category{}` kullaniminda raw dizi turlerinin *iterator_category* nested type'i bulunmadigi icin sentaks hatasi olusacaktir. Type traits'de tanimli adres turleri icin specializationdan faydalanarak soyle yazilabilir:
```C++
template <typename Iter>
int Distance(Iter x, Iter y)
{
    Distance_impl(beg, end, typename std::iterator_traits<Iter>::iterator_category{});
}
```
</details>
<!--  -->


**Ornek:** [Pointer turleri icin ayri, olmayan turler icin ayri implementasyon secimi](res/src/tag_dispatch02.cpp)  
<!-- 
TODO Aciklama ekle 

<details>
<summary><b>Aciklama</b> (Click to expand)</summary>


</details>
<!--  -->
