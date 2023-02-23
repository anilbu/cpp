# Error Handling

Bir program calisirken hatalar olabilir. Bu hatalarin temelde iki sebebi vardir ve farkli araclar kullanilarak hatalar yonetilir.

1. Programming errors  
   *Kodun yanlis olmasi*
   * compile-time (static) assertions  
     *Eger derleme zamaninda dogrulanmasi gereken kosullar saglanmadiginda programin calistirilmasi yanlis olacak durumlarin yakalanarak duzeltilmesi*  
     static_assert vb.
   * runtime (dynamic) assertions  
     *Programin calisma zamaninda yapilan dogrulamalar saglanmadiginda programin sonlandirilmasi icin gerekli durumlarin yakalanmasi*  
     abort termination vb.
2. Istisna durumlar  
   *Programin calisma zamaninda istisnai durumlarin olusmasi durumunda, kendini cagiran koda isini yapamadigini bildirmesi*  
   * Traditional error handling
   * Exception handling

<!-- 
> `<cassert>` baslik dosyasinda bulunan `assert` makrosunun kullanimini bilindigi varsayilmaktadir. 
-->

## Traditional Error Handling

> **Not**  
> Traditional error handling yontemleri ve neden oldugu problemlerden C++ exception handling konusuna giris amaciyla kisaca bahsedilecektir.

**Yontemler**
1. Fonksiyonun geri donus degeri ile hata bildirimi
   * Hata durumunda `nullptr` geri donulmesi
     `fopen`, `setlocale`, `malloc` vb.
   * Hata durumunda `non-zero` deger geri donulmesi
     `rename`, `atoi` vb.
   * Hata durumunda `sentinel` deger geri donulmesi
     `ftell` vb.
2. Out parameter ile hata bildirimi
3. Global error variable ile hata bildirimi
   `errno`
4. Bir yapinin icinde hata degiskeni barindirma
5. `setjmp`/`longjmp`

**Dezavantajlar**

* ctor'larin icinde olusan hatalarin bildirimi
  * geri donus degeri olmadigi icin
  * default ctor ile out parameter kullaniminin mumkun olmamasi
* Client kod'da hata kontrolunun zorlayici olarak yaptirilamamasi
* Hata isleyen kod ile logic kodun ic ice bulunmasi
  ```
  f1 => f2 => f3 => f4 => f5
  ```
  *Programin akisi f5'e olusan hatanin ornegin f2'de handle edilmesi icin gerekli control ifadeler zincirinin call chain icerisinde olusturulmasi gerekmektedir.*
* Birden fazla yontem var ve standarda dahil degiller.
  