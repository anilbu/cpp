# Temel Kavramlar

## Sentaks Hatasi
Dilin kurallarinin cignendigi durumlarda derleyicinin olusturdugu hatalardir.
* invalid code - valid code
* illegal code - legal code
* ill-formed - well-formed code

## Data Abstraction
Problem domain'inde varliklari soyut olarak temsil edilmesidir. 

## Undefined Behaviour (UB)
Dilin kurallarina gore derleyicinin kontrolunden sentaks hatasi olmadan gecen, ancak calisma zamaninda nasil bir durum olacagi konusunda bir garanti bulunmayan durumlardir.

Kesinlikle **kacinilmasi** gerekmektedir. Yazilan kodun calisiyor olmasi, UB olmadigi anlamina gelmemektedir!

> Programda UB soz konusuysa "**all bets are off**"


*Neden UB durumlari var?*  
Derleyici kodu tekrar duzenleyerek optimizasyon yapabilmesi icin tum durumlar tanimli degildir. Ancak optimizasyonun dogru olarak yapildigini garanti edilebilmesi icin, kodun icinde tanimsiz davranis durumunun olmadigi kabul edilmektedir.

**Ornekler**
* Otomatik omurlu bir degiskeni garbage value ile kullanmak.
* nullptr dereference etmek
* Dizileri tasirmak

## Unspecified Behavior
Derleyicinin nasil kod uretecegi konusunda herhangi bir sekilde baglayiciligin olmamasi durumudur. Kodda Unspecified Behavior bulunmasi bir hata degildir, ancak unspecified bir durumun davranisina guvenerek yazilan program problemlere neden olabilir.

**Ornek**
Asagidaki ifade icin hangi fonksiyona cagri once yapilir?
```C++
a = f1() + f2() + f3();
```
Farkli derleyiciler farkli sira ile cagirabilir. Hatta, ayni derleyici tarafindan unspecified behavior durumlarinda her zaman ayni kodu uretecegi dahi belli olmayabilir.
Yukaridaki fonksiyonlarin cagrilma sirasi program akisi icin onemli ise sorun teskil edebilir.

> :warning: Operator onceligi ile islemin hesaplanma sirasi birbirinden farkli seylerdir.

**Ornek**
Ozdes iki string'in ayni bellek alaninda tutulup tutulmayacagi derleyiciye bagli bir unspecified durumdur. Tutulabilir de tutulmayabilir de...

```C
const char* p1 = "text";
const char* p2 = "text";

if(p1 == p2) {
    // Bu blogun calismasi derleyicinin urettigi koda baglidir!
}
```

> :warning: Ayni derleyici tarafindan ayni unspecified durumlar icin her zaman ayni kodu uretecegi garanti edilmemektedir.

## Implementation-defined Behavior

Derleyicinin implementasyonuna bagli olarak, birden fazla secenek arasinda nasil kod uretegini dokumante ederek belirli bir secenegi uyguladigi durumlardir. Unspecified behavior'un bir alt kategorisidir.

**Ornek**  
`char` turunun `signed` yada `unsigned` olmasi derleyiciye bagli bir durumdur.

**Ornek**  
`x << 4` ifadesinden `x` degeri signed negatif bir deger oldugunda, sola kaydirma isleminde eklenen bit degeri `0` mi `1` mi olacagi implementation-defined bir durumdur.

> :warning: Implementation-defined durumlar portability (derleyici degistirme) konusunda problem cikarabilir.

## Linkage
Kisaca; birden fazla kaynak dosyasinda kullanilan ayni isimler ayni varliga ait ise, buna **external linkage** denir.  
Ayni isim farkli kaynak dosyalarda farkli varliga ait ise, **internal linkage** denir.  
Global olmayan yerel degiskenlerin baglanti durumu ise **no linkage** olarak adlandirilmaktadir.  

## contextual keyword
*Baglamsal anahtar sozcuk*  

Belirli bir baglam icinde iken anahtar sozcuk olarak davranirken, baglam disinda iken ahtar sozcuk olarak davranmayan *isimlendirmede kullanilabilen* kelimelerdir.

C++'daki contextual keywords:
* `override`
* `final`
* <!-- TODO: tamamla  -->

<!--  -->

# Terminoloji

* **implicit**: *(Ortulu, kapali, gizli)* Acikca bir kod yazilmadan, dilin kurallari geregi, gizli olarak anlamin ifade edilmesidir.
* **explicit**: *(Acikca)* Kod ile acik bir talimat belirtilerek anlamin ifade edilmesidir.
* **ambiguity**: Birden fazla secenek olmasina ragmen seceneklerin kendi arasinda bir secim kriterinin olmamasi durumu.
* **source file**: Kaynak dosya (preproc. calismadan onceki durumu)
* **translation unit**: Ceviri birimi (preproc. calistiktan sonra uretilen durumu, derleyicinin gordugu)
* **mutable**: Degistirilebilen.  
* **immutable**: Degistirilemeyen.  
* **best practice**: Iyi uygulama  
* **bad practice**: kotu uygulama  
* **pattern**: Programlama dilinden bagimsiz olarak kullanilan kodlama yapilari  
* **anti-pattern**: Yaygin kullanimi olan ama aslinda kullanimi kotu kaliplar
* **idiom**: Tamamen programalama diline bagli (dile ozgu) kodlama yapilari  
* **parameter**: *(formal parameter)* Fonksiyonun parametre degiskenine verilen isim
* **argument**:  *(actual parameter)* Fonksiyon cagrisinda degeri gonderilen ifadelere verilen isim
* **Shallow copy**: (Memberwise copy) Bir nesnenin sığ kopyası, özellikleri kopyanın yapıldığı kaynak nesneyle aynı referansları paylaşan (aynı temel değerleri işaret eden) bir kopyadır.
* **Deep copy**: Bir nesnenin derin kopyası, özellikleri kopyanın yapıldığı kaynak nesneyle aynı temel değerleri işaret etmesine ragmen referansları paylaşmayan bir kopyadır.
* **DRY**: don't repeat yourself
