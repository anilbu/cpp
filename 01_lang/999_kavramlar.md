# Maximal Munch Rule
Derleyici her zaman en uzun token'i olusturacak bicimde tokenizing yapar.

[Soru](sorular/soru2.cpp)
```C++
int x = 5, y = 9;
int a = x+++y;

cout << "x = " << x << endl;  // 6
cout << "y = " << y << endl;  // 9
cout << "a = " << a << endl;  // 14
```
`x+++y` ifadesi x, ++, + ve y olarak tokenize edilir.

# Most vexing parse
*-Scott Meyers*
Belirli durumlarda, bir nesne parametresinin oluşturulması ile bir işlevin türünün belirtilmesi arasında ayrım yapilamiyor. Bu durumlarda, derleyicinin satırı bir **işlev tipi belirtimi** olarak yorumlamana most vexing parse denilmektedir.

Orn, nesne tanimlama (objimplementing
```C++
B bx( A() );  // Bu bir fonksiyon declarationdir!
B bx{ A() };  // object inst.
B bx( A{} );  // object inst.
```


# AAA (almost always auto)
`auto` kullaniminin hakkinda farkli gorusler bulunuyor. Bircok durumda kullanim kolayligi saglarken, bazi durumlarda auto kullanimi kod kalitesini cok dusmesine neden olabilmektedir. 
1. Tur yanlis yazilmis olabilir. Cogu durumda derleyici syntax hatasi verirken, bazi durumlarda gecerli bir syntax olusturabilir.
   ```C++
   std::vector<std::string> svec;
   
   std::pair<std::vector<std::string>::iterator,std::vector<std::string>::iterator> result = std::minmax_element(svec.begin(), svec.end());
   ```
   yerine
   ```C++
   auto result = std::minmax_element(svec.begin(), svec.end());
   ```
2. Bildirimin degismesi durumunda `auto` kullanilmadiginda turlerin duzenlenmesi gerekir.
   ```C++
   int foo();
   
   auto x = foo();
   ```
   `foo()`nun bildiriminde geri donus turunun degistigini varsayin.
3. Bu tarz durumlar cesitlendirilerek orneklendirilebilir...


# as if rule
Derleyici standartlarin tanimina gore kaynak kodunun karsiliginda bire bir kod uretmek zorunda degildir. Kaynak kodda anlatilan davranis eger programin calismasi acisinda `observable behavior` degismedigi surece derleyici kaynak kodunuzu istedigi gibi duzenleyebilir.

* dead code elimination
* inline extension
* loop unrolling
* loop reversal
* [bknz: Wikipedia - Optimizing compiler]([https://en.wikipedia.org/wiki/Optimizing_compiler)
* vb...

Derleyici bu optimizasyonlari gerceklestirirken kaynak kodda **UB** bulunmadigini varsayarak gerceklestirmektedir. 

Derleyiciler genellikle bu optimizasyonlarin kapatilabilmesini saglayan **flag**'lere sahiptir.
Idiomatic yapilar kodun anlasilmasini kolaylastirmasinin yani sira genellikle iyi optimize edilebiliyor olmalaridir.

> “Premature optimization is the root of all evil.” *-Donald Knuth*

C++ dilinin C'den farklarindan biri derleyicinin kod yazabiliyor olmasidir. (Generic programming/templates)


# type-punning
type punning is any programming technique that subverts or circumvents the type system of a programming language in order to achieve an effect that would be difficult or impossible to achieve within the bounds of the formal language.

# static binding
(early binding)
fonksiyon cagrisi compile-time'da iliskilendiriliyor.  

# dynamic binding
(late binding)
fonksiyon cagrisi runtime'da iliskilendiriliyor.

# name hiding
Farkli scopelardaki ayni isimli nesnelerin birbirini gizlemesi.

# header only library
Sadece header dosyalarindan olusan kutuphaneye denir. 

# data hiding
Sinifin implementasyon detaylarinin kodu kullanan kisilerden gizlenerek, hatali kullanim veya ozel durumlarin ogrenilmesi gibi bazi problemlerin engellemektir.

# static initialization fiasco
Global sinif nesneleri bildirim sirasi ile hayata getirilmektedir. Ancak, farkli kaynak dosyalarda tanimlanmis global sinif nesnelerinin hayata gelme sirasi dil tarafindan belirli degildir. Static initialization fiasco, bu durumdan kaynakli problemleri ifade eder.

# RAII
*Resource Accusation Is Initialization*

Bir nesne hayata getirildiginde bir yada birden fazla kaynak elde etmesi gerekebilir.
Nesnenin hayati bittiginde bu kaynaklari iade etmesi gerekir.

Bu kaynaklar bellek, dosya, db baglantisi, network baglantisi vb. olabilir.

* Tipik olarak `ctor` ile kaynaklar elde edilir, `dtor` ile kaynaklar iade edilir.
* Tipik olarak smart pointer'lar ile birlite kullanilir.

[Ornek: Dosya acma/kapama icin RAII Psuedo Impl. Ornegi](res/src/raii01.cpp)
[Ornek: Logger](res/src/raii02.cpp)

# copy & swap idiom
TODO


# NVRO
`Named Return Value Optimization (NRVO)` fonksiyon icerisinde bulunan bir yerel sinif nesnesinin geri donulmesidir. NRVO optimizasyonu mandatory olmamasi nedeniyle dilin kurallarina gore copy ctor cagrilabiliyor durumda olmasi zorunludur.
```C++
Myclass func()
{
  Myclass ret;

  // buradaki kodlar ret nesnesini kullaniyor olabilir

  return ret;
}
```
```C++
auto x = func();  // ret nesnesi x'in oldugu yerde olusturulacak.
```

# ABI
`Abstract binary interface`
<!-- TODO tamamla -->


# first-class functions
A programming language is said to have First-class functions when functions in that language are treated like any other variable.


# Allocator kavrami

Dinamik bellek ihtiyacinin karsilanmasi ve kullanilmasi islemlerini gerceklestiren turdur.

STL ve diger kutuphanelerde bulunan containerlar genellikle varsayilan olarak `std::allocator` turu uzerinden dinamik bellek alani kullanmaktadir.

`std::allocator` turu; `new` ve `delete` operatorlerini kullanmaktadir. global `new`/`delete` fonksiyonlari overload edilmeden bellek tahsis davranisi degistirmek isteniyor ise, **allocator** degistirilebilir olmalidir.
  
* ```C++
  template <typename T, typename TTraits = std::char_traits<T>, typename TAlloc = std::allocator<T>>
  class Basic_string;
  
  using String = Basic_string<char>;
  ```
  ```C++
  Basic_string<char, char_traits<char>, allocator<char>> bs;
  String s;
  ```
* ```C++
  using Ostream = Basic_ostream<char, std::char_traits<char>>;
  ```
  ```C++
  Basic_ostream<char, char_traits<char>> bos;
  Ostream os;
  ```
  
# Serialize/Deserialize
Bir sinif nesnesinin state'ini text olarak ifade edilmesine **serialization**, bu text'den nesneyi geri olusturmaya **deserialization** denilir.
* LE/BE 
* Pointer degiskenler
