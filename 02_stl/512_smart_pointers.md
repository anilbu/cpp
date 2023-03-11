# Smart Pointers

Dinamik omurlu kaynak veya nesnelerin hayatini kontrol eden *pointer-like* sinif sablonlaridir.  
`<memory>` baslik dosyasinda bulunurlar.

**Smart pointer categories**  
* `unique_ptr`: Tek sahiplik semantigi
* `shared_ptr`: Paylasilan sahiplik semantigi
* `weak_ptr`: Paylasilan sahiplik semantigi ile yonetilen bir nesneyi gozlemleme amaciyla referens edilebilmesini saglamaktadir.

> :information_source: `auto_ptr` sinifi [C++11] ile deprecate edilerek dilden kaldirildi.

**raw (naked) pointer kullanimindan kaynakli problemler**  
* Raw pointer'in isaret ettigi adres alaninin storage kategorisi implementasyona bakilmadan anlasilamiyor.  
  *Delete edilmeli mi edilmemeli mi? Nerede/ne zaman delete edilmeli?*  
  * delete edilmesi gereken bir nesnenin delete edilmemesi
  * double deletion
* Bir diziyi mi gosteriyor yoksa objeyi mi gosteriyor bilinmiyor.  
  *Nasil delete edilmeli? `delete` vs `delete[]`*
* Ayni kaynagi gosteren baska pointerlar var mi bilmiyor.  
  *Eger varsa dangling pointer ve/ya double deletion olusma durumlarinin yonetilmesi gerekir.*  
  *Delete edilen nesneyi isaret eden pointer'larin bu durumdan haberdar olmamasi*  
* Exception safety  
  *Raw pointer kullanilarak tutulan bir nesnenin olusturulmasi ile delete arasinda exception firlatilirsa delete kodu calismayacaktir. Ancak otomatik omurlu bir smart pointer nesnesi ile kontrol edilen bir dinamik kaynak serbest birakilacaktir.*  
  [Ornek 1: Stack unwinding](res/src/smart_ptr01.cpp)  
  *Benzer sekilde ctor'da exception throw edilmesi durumunda raw pointer ile tutularak initialize edilmis bir veri elemani icin dtor calistirilmayacaktir.*  
  [Ornek 2: Ctor'da exception throw edilmesi](res/src/smart_ptr02.cpp)  

  > :pushpin: Dinamik omurlu nesneler icin [stack unwinding](../01_lang/325_exception_handling.md#stack-unwinding) surecinde exception yakalandigi zaman otomatik omurlu nesnelerin dtor cagrilmaktadir.
  
<!-- > Programci basini belaya sokmaya niyetli ise bir yolunu bulup... -->