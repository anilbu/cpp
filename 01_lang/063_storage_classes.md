# Storage Classes
*storage duration*

Storage class, bir nesnenin o nesne icin ayrilmis yada ayrilacak olan bellek alaninda hangi sure ile duracagini belirtir.

* Automatic storage  (stack)  
  Kodun yurutulmesi suresince bellekte kalan degiskenlerdir. Compile-time'da belirlenir.
* Static storage (.data segment)  
  Hayata geldikten sonra kaybolmayan nesnelerin storage turudur. Compile-time'da belirlenir.
* Dynamic storage (heap)  
  Hayata gelmesi/yok edilmesi programci tarafindan belirlenmis nesnelerin storage turudur. Runtime'da belli olur.
* Thread-local storage

> scope isimlerin niteligi, storage class nesnelerin niteligidir.


> **Hatirlatma**
> Global nesneler hayata main fonksiyonu cagrilmadan once gelir.

> **Storage categories**
> 
> *Ileride daha detayli anlatilacak.*  
> 
> Kisaca; nesnelerin olusturulduklari tipik bellek alanlari:
> ```
> static omurlu sinif nesneleri  
>   .data segmenti
> 
> otomatik omurlu sinif nesneleri
>   stack
> 
> dinamik omurlu nesneler
>   heap/free store
>  
> thread_local
>   ??
> ```