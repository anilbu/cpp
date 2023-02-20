# Temel Kavramlar


## Data Abstraction
Problem domain'inde varliklari soyut olarak temsil edilmesidir. 


## Undefined Behaviour (UB)
Dilin kurallarina gore derleyicinin kontrolunden sentaks hatasi olmadan gecen, ancak calisma zamaninda nasil bir durum olacagi konusunda bir garanti bulunmayan durumlardir.

Kesinlikle **kacinilmasi** gerekmektedir. Yazilan kodun calisiyor olmasi, UB olmadigi anlamina gelmemektedir!

*Neden UB durumlari var?*
Derleyici kodu tekrar duzenleyerek optimizasyon yapabilmesi icin.

**Ornekler**
Otomatik omurlu bir degiskeni garbage value ile kullanmak.
nullptr dereference etmek
Dizileri tasirmak


## Unspecified Behavior
Derleyicinin nasil kod uretecegi konusunda herhangi bir baglayici olmamasi durumudur. Kodda Unspecified Behavior bulunmasi bir hata degildir, ancak unspecified bir durumun davranisina guvenerek yazilan program problemlere neden olabilir.

**Ornek**
Asagidaki ifade icin once hangi fonksiyona cagri yapilir?
```C++
a = f1() + f2() + f3();
```
Farkli derleyiciler farkli sira ile cagirabilir. Hatta, ayni derleyici tarafindan unspecified behavior durumlarinda her zaman ayni kodu uretecegi dahi belli olmayabilir.
Yukaridaki fonksiyonlarin cagrilma sirasi program akisi icin onemli ise sorun teskil edebilir.

**Ornek**
Ozdes iki string'in ayni bellek alaninda tutulup tutulmayacagi derleyiciye bagli bir unspecified durumdur. Tutulabilir de tutulmayabilir de!
    
```C
const char* p1 = "text";
const char* p2 = "text";

if(p1 == p2) {
    // Bu blogun calismasi derleyicinin urettigi koda baglidir!
}
```


## Implementation-defined Behavior

Unspecified behavior'un bir alt kategorisidir. Derleyici, birden fazla secenek arasinda nasil kod uretegini dokumante ederek belirli bir secenegi uygulamak zorundadir.

**Ornek**
`char` turunun `signed` yada `unsigned` olmasi derleyiciye bagli bir durumdur.

**Ornek**
`x << 4` ifadesinden `x` degeri signed negatif bir deger oldugunda, sola kaydirma isleminde eklenen bit degeri `0` mi `1` mi olacagi implementation-defined bir durumdur.

> **DIKKAT!**
> Implementation-defined durumlar portability (derleyici degistirme) konusunda problem cikarabilir.


## contextual keyword
*Baglamsal anahtar sozcuk*  

Belirli bir baglam icinde iken anahtar sozcuk olarak davranirken, baglam disinda iken ahtar sozcuk olarak davranmayan *isimlendirmede kullanilabilen* kelimelerdir.

C++'daki contextual keywords:
* `override`
* `final`






<!--  -->

# Terminoloji

* `implicit`: Ortulu - kapali - gizli
* `explicit`: Acik
* `ambiguity`: Birden fazla secenek olmasina ragmen seceneklerin kendi arasinda bir secim kriterinin olmamasi durumu.
* `source file`: Kaynak dosya (preproc. calismadan onceki durumu)
* `translation unit`: Ceviri birimi (preproc. calistiktan sonra uretilen durumu, derleyicinin gordugu)
* `best practice`: Iyi uygulama  
* `bad practice`: kotu uygulama  
* `pattern`: Programlama dilinden bagimsiz olarak kullanilan kodlama yapilari  
* `anti-pattern`: Yaygin kullanimi olan ama aslinda kullanimi kotu kaliplar
* `idiom`: Tamamen programalama diline bagli (dile ozgu) kodlama yapilari  
* `parameter`: (formal parameter) Fonksiyonun parametre degiskenine verilen isim
* `argument`:  (actual parameter) Fonksiyon cagrisinda degeri gonderilen ifadelere verilen isim
* `Shallow copy`: (Memberwise copy) Bir nesnenin sığ kopyası, özellikleri kopyanın yapıldığı kaynak nesneyle aynı referansları paylaşan (aynı temel değerleri işaret eden) bir kopyadır.
* `Deep copy`: Bir nesnenin derin kopyası, özellikleri kopyanın yapıldığı kaynak nesneyle aynı temel değerleri işaret etmesine ragmen referansları paylaşmayan bir kopyadır.
* `dry`: don't repeat yourself
