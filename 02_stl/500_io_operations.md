# I/O operations

C++ includes the following input/output libraries: an OOP-style stream-based I/O library, print-based family of functions (since C++23), and the standard set of C-style I/O functions.

## stdin, stdout, stderr
```C++
#define stdin  /* implementation-defined */     (1)	
#define stdout /* implementation-defined */     (2)	
#define stderr /* implementation-defined */     (3)
```
Three text streams are predefined. These streams are implicitly opened and unoriented at program startup.

1) Associated with the standard input stream, used for reading conventional input. At program startup, the stream is fully buffered if and only if the stream can be determined not to refer to an interactive device.
2) Associated with the standard output stream, used for writing conventional output. At program startup, the stream is fully buffered if and only if the stream can be determined not to refer to an interactive device.
3) Associated with the standard error stream, used for writing diagnostic output. At program startup, the stream is not fully buffered.

## Stream-based I/O

C'den farkli olarak C++ da giris cikis islemleri 
* Belirli olcude kalitim hiyerarsi bulunur
* Belirli olcude runtime-poly 
* Sinif sablonlarindan olusmaktadir. *`ios_base` sinifi haric*

<center>
<img src="res/img/std-io-complete-inheritance.drawio.svg" width="480"/><br/>
<i>Sekil: C++ I/O Hiyerarsisi</i>
</center>

Stream'de akisda belirtilen bytelari ifade eden karakter parametresi bir template parametresi ile ifade edilmektedir. 

```C++
using ostream = std::basic_ostream<char, char_traits<char>>;
```

`basic_ios<CharT, Traits>` giris yada cikis olmasindan bagimsiz olarak bir akisi temsil etmektedir.

```C++
basic_ios::binary;
basic_ios<char>::binary;        
basic_ostream<char>::binary;    // ostream
basic_ofstream<char>::binary;   // ofstream fstream header'inda
```

> :triangular_flag_on_post: 
> Bazi sistemlerde *(Windows)* `char` turu yerine `wchar_t` turu kullanilmaktadir.
> Eger `wchar_t` kullanilmak isteniyor ise `ios` yerine `wios` kullanilabilmektedir.
> ```C++
> using wstring = basic_string<wchar_t>;
> ```

* `basic_ostream` ve `basic_istream` **[virtual inheritence](../01_lang/299_multiple_inheritance.md#virtual-inheritance)** ile `basic_ios` sinifindan turetilmislerdir.
* `basic_ostream` sinifinin `operator<<` fonksiyonu vardir.
* `basic_istream` sinifinin `operator>>` fonksiyonu vardir.

Streamden giris/cikis yapan byte'lar bir kez akmaktadir. Ancak, arada bir bufferlama mekanizmasi (`basic_streambuf`/`basic_stringbuf`) *cogunlukla* bulunmaktadir.

## Formatli I/O Islemleri

Genel olarak `operator<<` global fonksiyonu overload edilerek yapilmaktadir. Butun `operator<<` geri donus degeri akim nesnesinin kendisidir.

```C++
cout << 10 << 3.14;     // cout.operator<<(10).operator<<(3.14);
```

> **DIKKAT!**
> `operator<<` overloadlarindan ikisi cok karistirilmaktadir:
> ```C++
> operator<<(cout, "necati");  // operator<<(ostream&, const char*);  prints necati
> operator<<(cout, 'A');       // operator<<(ostream&, char);         prints A
> cout.operator<<("necati");   // basic_ostream::operator<<(void*);   prints address
> cout.operator<<('A');        // basic_ostream::operator<<(int);     prints 65
> ```

*inserter'i olan siniflar:*
```C++
cout << std::complex{};             // var
cout << std::bitset{};              // var
cout << std::pair<int, int>{};      // yok
cout << std::tuple<int, int>{};     // yok
cout << std::unique_ptr<int>{};     // var ama nesnenin degil pointer'in
cout << std::shared_ptr<int>{};     // var ama nesnenin degil pointer'in
cout << std::vector<int>{};         // yok
cout << std::array<int>{};          // yok
```

C'de printf ile format specifiers *`%` ile baslayan karakter sekanslari* ile verilmektedir.

Her I/O nesnesinin ciktinin nasil olusturulacagini belirlemek amaciyla kullandigi bir format state *(durum)* bilgisine vardir.

Formatlama 2 gruba ayrilmaktadir
1. `ios_base::fmtflags`
2. <!-- TODO: ??? -->  


### `ios_base::fmtflags`

On/off bayraklari: [`ios_base::fmtflags`](https://en.cppreference.com/w/cpp/io/ios_base/fmtflags) formatlama ozelliklerinin bir kismini tutan state nesnesidir.

```C++
cout << (10 > 5);             // prints 1
cout.setf(ios::boolalpha);    // state degistirilir
cout << (10 > 5);             // prints true
cout << (10 > 5);             // prints true
cout.unsetf(ios::boolalpha);  // state degistirilir
cout << (10 > 5);             // prints 1
```

* Format state `setf()` fonksiyonu ile aktif edilebilmete, `unsetf()` ile temizlenebilmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  [Ornek](res/src/io_fmtflags01.cpp)
  ```C++
  cout.setf(ios_base::boolalpha);
  cout << true << false;
  cout.unsetf(ios_base::boolalpha);
  ```
  </details>
  <!--  -->
  
* `flags()` fonksiyonu ile state elde edilebilmektedir.  
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  [Ornek](res/src/io_fmtflags02.cpp)
  ```C++
  const auto tmp_flags = os.flags();
  os.setf(ios_base::boolalpha | ios_base::uppercase | ios_base::showbase);
    
  // do operations...
    
  os.flags(tmp_flags);
  ```
  **UYARI** Yukaridaki yontem sadece `fmt_flags` icin uygulanabilir, tum format stateleri flagler ile tutulmamaktadir. Tum format stateleri icin ayri bir `ostream` nesnesi kullanilabilir:
  ```C++
  ostream oss{ cout.rdbuf() };
  oss.setf(ios_base::boolalpha | ios_base::uppercase | ios_base::showbase);
  // do operations...
  ```
  `oss` stateleri degisti ancak `cout` stateleri degismedi.
  </details>
  <!--  -->

* Format state flagleri gruplara gore maskelenmektedir.  
  dec, hex ve octal icin basefield maskesi:
  [Ornek](res/src/io_fmtflags03.cpp)
  ```
        dho
  000000xxx000000000
  000000111000000000  ios::basefield
  000000100000000000  ios::dec
  000000010000000000  ios::hex
  000000001000000000  ios::oct
  ```

| Constant           | Explanation                                                                                                      |
| ------------------ | ---------------------------------------------------------------------------------------------------------------- |
| `ios::dec`         | use decimal base for integer I/O                                                                                 |
| `ios::oct`         | use octal base for integer I/O                                                                                   |
| `ios::hex`         | use hexadecimal base for integer I/O                                                                             |
| `ios::basefield`   | `dec` \| `oct` \| `hex`. Useful for masking operations                                                           |
| `ios::left`        | left adjustment (adds fill characters to the right)                                                              |
| `ios::right`       | right adjustment (adds fill characters to the left)                                                              |
| `ios::internal`    | internal adjustment (adds fill characters to the internal designated point)                                      |
| `ios::adjustfield` | `left` \| `right` \| `internal`. Useful for masking operations                                                   |
| `ios::scientific`  | generate floating point types using scientific notation, or hex notation if combined with fixed                  |
| `ios::fixed`       | generate floating point types using fixed notation, or hex notation if combined with scientific                  |
| `ios::floatfield`  | `scientific` \| `fixed`. Useful for masking operations                                                           |
| `ios::boolalpha`   | insert and extract bool type in alphanumeric format                                                              |
| `ios::showbase`    | generate a prefix indicating the numeric base for integer output, require the currency indicator in monetary I/O |
| `ios::showpoint`   | generate a decimal-point character unconditionally for floating-point number output                              |
| `ios::showpos`     | generate a + character for non-negative numeric output                                                           |
| `ios::skipws`      | skip leading whitespace before certain input operations                                                          |
| `ios::unitbuf`     | flush the output after each output operation                                                                     |
| `ios::uppercase`   | replace certain lowercase letters with their uppercase equivalents in certain output operations                  |

#### `ios::hex`/`ios::oct`/`ios::dec`
* **Mask**: `ios::basefield`  
* **default**: 10'luk sayi sisteminde
* Birden fazla sayi sistemi bayragi set edilirse `ios::dec` kullanilir.  
[Ornek](res/src/io_fmtflags04.cpp)  

#### `ios::fixed`/`ios::scientific`/`ios::hexfloat`
* **Mask**: `ios::floatfield`  
* **default**: buyukluge ve hassasiyete gore karar verilmekte.
* Birden fazla sayi sistemi bayragi set edilirse `ios::hexfloat`[C++11] kullanilir.  

  | fixed | scientific | representation       |                 |
  | :---: | :--------: | -------------------- | :-------------- |
  |   0   |     0      | 3.14                 | (default)       |
  |   1   |     0      | 3.140000             | fixed           |
  |   0   |     1      | 3.140000e+00         | scientific      |
  |   1   |     1      | 0x1.91eb851eb851fp+1 | hexfloat[C++11] |

  **Precision**  
  `precision()`: precision get/set  

  **`ios::showpoint`**  
  Ondalik sayilarda herzaman `.` yazdirilmasini saglar.   

  [Ornek](res/src/io_fmtflags05.cpp)  

#### `ios::left`/`ios::internal`/`ios::right`
* **Mask**: `ios::adjustfield`
* **default**: `ios::left`

  | Orientation     |             |
  | --------------- | ----------- |
  | `ios::left`     | `12345____` |
  | `ios::internal` | `+___12345` |
  | `ios::right`    | `____12345` |

  **Output width**  
  `width()`: Output genisligi get/set  
  * Normalde formatlama ozellikleri kalici olarak set edilirken `width` **sadece cikisi yapilacak ilk oge** icin gecerli olmaktadir.
  * Yazilacak karakter sayisi width'den daha genis ise normalde yazdirildigi gibi *(truncation yapilmadan)* yazdirilir.
  
  **fill character**  
  `fill()`: fill karakteri get/set  
    
  [Ornek](res/src/io_fmtflags06.cpp)


### Manipulator fonksiyonlari
`std::ios_base::fmtflags`'da bulunan alanlari **set** etmek icin karsilik `std` isim alaninda ayni isimli global fonksiyonlar bulunmaktadir. **unset** icin `no + isim` olarak fonksiyonlar bulunmaktadir.

<details>
<summary><b>Bu fonksiyonlar su sekilde tasarlanmistir</b> (Click to expand)</summary>

[Ornek](res/src/io_manip01.cpp)  
```C++
class Ostream {
public:
  // ...
  Ostream& operator<<(Ostream& (*fp)(Ostream&))
  {
    fp(*this);
  }
  // ...
};

Ostream& manip_func(Ostream&)
{
  // do formatted output operations
  return os;
}
```
```C++
Ostream os;
os << manip_func;  // os.operator<<(manip_func);
                   // Ostream::operator<<(Ostream&(*)(Ostream&)) imzali fonksiyon overloadu
```
</details>
<!--  -->

[Ornek: Custom manipulator](res/src/io_manip02.cpp)  
[Ornek: Custom manipulator (RAII)](res/src/io_manip03.cpp)  
[Ornek: delimiter](res/src/io_manip04.cpp)  
[Ornek: starline](res/src/io_manip05.cpp)  
[Ornek: istream manip](res/src/io_manip06.cpp)  

**Parametreli manipulatorler**  
`<iomanip>` baslik dosyasinda bulunan parametre alabilen fonksiyonlardir.
```C++
cout << setw(12);
cout << setfill('_');
cout << setprecision(3);
```
[Ornek](res/src/io_manip07.cpp)  

> :warning: 
>  [`std::endl`](https://en.cppreference.com/w/cpp/io/manip/endl) bir manipulator fonksiyonudur ve stream'i flush eder.
> ```C++
> std::ostream& endl(std::ostream& os)
> {
>   os.put('\n');
>   os.flush();
>   return os;
> }
> ```

<!-- 

### `std::format` [C++20]

[std::format](https://en.cppreference.com/w/cpp/utility/format/format)

C++20 standadi ile `std::format` dile eklendi. *[[Video: Victor ... std::format tanitimi]()]*

* `<format>` baslik dosyasinda bulunur.

[[Standard format specification](https://en.cppreference.com/w/cpp/utility/format/formatter#Standard_format_specification)]
[[Ornekler](res/src/format01.cpp)]

> :warning: 
> GCC 13 ve sonrasinda destek verilmektedir.

-->

## Condition state

Her stream nesnesinin durumunu belirten `ios::iostate` turunden bir **condition state**'i bulunmaktadir. Eger stream nesnesinde herhangi bir hata yok ise degeri `0`'dir. 

* Eger stream iyi durumda ise `good()` fonksiyonu `true` deger dondurmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  * ```C++
    if(cin.good())
        cout << "stream iyi durumda\n";
    ```
  * ```C++
    if(cin) {  // cin.operator bool() ---> cin.good()
      cout << "stream iyi durumda\n";
    }
    ```
  </details>
  <!--  -->
* Eger stream'de son yapilan islem hataya *(orn: format uyumsuzlugu)* neden olmus ise `fail()` fonksiyonu `true` deger dondurmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
    * ```C++
      if(cin.fail())
        cout << "stream hata durumunda\n";
      ```
    * ```C++
      if(!cin) { // cin.operator!() ---> cin.fail()
        cout << "stream hata durumunda\n";
      }
      ```
  </details>
  <!--  -->
* Eger stream'de karakter kalmamis ise `eof()` fonksiyonu `true` deger dondurmektedir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  if(cin.eof())
    cout << "stream eof durumunda\n";
  ```
  </details>
  <!--  -->
  
  > :triangular_flag_on_post: 
  > Windows'da `cin`'de eof durumu `CTRL+Z`, Linux/bash'de `CTRL+D` ile olusturulabilir. 
  
* Eger stream recovery yapilamayacak bir durumda ise `bad` state'de bulunur.

[Ornek](res/src/io_state01.cpp)  
[Ornek](res/src/io_state02.cpp)  

<!-- Ders 48 -->

stream sinifinin `rdstate()` fonksiyonu ile *condition state*'ine erisilebilmektedir. 
```C++
cin.rdstate() & ios::goodbit
cin.rdstate() & ios::failbit
cin.rdstate() & ios::eofbit
cin.rdstate() & ios::badbit
```

Bir stream nesnesi, `fail` durumunda ise, yeniden okuma/yazma islemi yapilabilmesi icin `good` state'ine getirilmesi gerekmektedir. 
[Ornek](res/src/io_state03.cpp)  

`iostream::clear()` fonksiyonu stream state'ni temizlemektedir.  
`iostream::setstate()` fonksiyonu stream state'ni set etmektedir.  
```C++
cin.clear(ios::failbit);        // condition_state = failbit
cin.setstate(ios::failbit);     // condition_state |= failbit
```

```C++

```

[Ornek](res/src/io_state04.cpp)

### String I/O Streams

|               | inherited from | Interface     |           |
| ------------- | -------------- | ------------- | --------- |
| istringstream | istream        | Okuma         | *sscanf*  |
| ostringstream | ostream        | Yazma         | *sprintf* |
| stringstream  | iostream       | Okuma + Yazma |           |

* `<sstream>` baslik dosyasinda bulunur.
* `ostringstream::str()` fonksiyonu ile bufferdaki karakterler set/get edilebilmektedir.
* [`istream_iterator`](100_iterators.md#istream_iterator)/[`istream_iterator`](100_iterators.md#ostream_iterator) ile birlikte kullanilabilir.

[Ornek: ostringstream](res/src/io_sstream01.cpp)  
[Ornek: istringstream](res/src/io_sstream02.cpp)  
[Ornek:  stringstream](res/src/io_sstream03.cpp)  
[Ornekler](res/src/io_sstream04.cpp)  



### File I/O Streams

|          | inherited from | Interface     |           |
| -------- | -------------- | ------------- | --------- |
| ifstream | istream        | Okuma         | *fscanf*  |
| ofstream | ostream        | Yazma         | *fprintf* |
| fstream  | iostream       | Okuma + Yazma |           |

* `<fstream>` baslik dosyasinda bulunur.
* Default ctor'lari bulunur.  
  `open()` fonksiyonu ile dosya acilabilmektedir.  
  `close()` fonksiyonu ile dosya kapatilabilmektedir.  
  `is_open()` fonksiyonu ile yonetilen bir dosya var mi test edilebilmektedir.  
  
* `fstream` nesneleri kopyalamaya karsi kapatilmis ancak tasimaya aciktirlar.
  
* `fstream` nesnelerinin tamami RAII idiom'unu kullanmaktadir.  
  *Ctor* ile bir dosyanin acilmasi saglanabilmektedir.   
  *Eger dtor cagrildigi bir dosyanin yonetimi kontrol ediliyor ise dosyayi kapatacaktir.*  

  > **Dikkat**  
  > `ofstream` turunden bir nesnenin olmasi, bu nesnenin bir dosya ile iliskilendirilmis oldugu anlamina gelmemektedir.
  >    * `ofs` hicbir dosya ile ilgili degildir ama hayattadir.
  >    * `ofs` belirli bir timepoint'deki bir dosyayi yonetmektedir.
  >    * Dosya islemleri tamamlanmis ancak `ofs` hala hayatta olabilir.

* [`istream_iterator`](100_iterators.md#istream_iterator)/[`istream_iterator`](100_iterators.md#ostream_iterator) ile birlikte kullanilabilir. [[Ornek](res/src/io_fstream09.cpp)]

**openmodes**  
| constants        |    default in    | desc                                                        |
| ---------------- | :--------------: | ----------------------------------------------------------- |
| `ios::in`        | ifstream/fstream | open for reading                                            |
| `ios::out`       | ofstream/fstream | open for writing                                            |
| `ios::app`       |                  | seek to end of stream before each write                     |
| `ios::binary`    |                  | open in *binary mode*                                       |
| `ios::trunc`     |     ofstream     | discard the contents of the stream when opening             |
| `ios::ate`       |                  | *(at end)* seek to the end of stream immediately after open |
| `ios::noreplace` |                  | open in exclusive mode [C++23]                              |

* `ifstream`'de `ios::in`, `ofstream`'de `ios::out` her zaman varsayilan olarak set edilmektedir. 

[Ornek: ofstream](res/src/io_fstream01.cpp)  
[Ornek: ifstream](res/src/io_fstream02.cpp)  
[Ornek: is_open()](res/src/io_fstream03.cpp)  
[Ornek: primes](res/src/io_fstream07.cpp)  
[Ornek: Tekrar](res/src/io_fstream08.cpp)  

> :warning: 
> Asagidaki kodda donguden cikilabilmesi icin `ifs` failed state'e girmesi gerekmektedir.  
> Tekrar dosya acilabilmesi icin stream'in **good-state**'e geri getirilmesi gerekmektedir.  
> [Ornek](res/src/io_fstream04.cpp)
> ```C++
> // ...
> 
> char c;
> while(ifs.get(c)) {   // donguden cikarken ifs failed oldu
>   // ...
> }
> 
> ifs.clear();  // clear failed state
> 
> ifs.close();
> ifs.open();
> ```

> :warning: 
> Windows'da text mode'da acilmis bir dosyaya okuma/yazma yapilirken  `'\n'` karakteri `'\r\n'`'e *{13, 10}* donusturulmektedir.
> 
> Text modunda acilmis bir dosyada 26 degerine sahip bir byte okunursa `EOF` anlami tasimaktadir.

###  Exception handling in File I/O
Dosya islemleri varsayilan olarak exception gondermek yerine *fail* durumuna dusmektedir.  
Ancak stream nesnelerinin `basic_ios::exception()` fonksiyonu ile stream nesnesinin belirtilen durumlarda `std::ios_base::failure` turunden bir exception gondermesi saglanabilmektedir.  

```C++
auto state = ifs.exceptions();
std::cout << "state = " << state << '\n'; // good state

// eger failbit set edilirse exception gonderilsin
ifs.exception(ios::failbit);    
```

[Ornek: failed (default)](res/src/io_fstream14.cpp)  
[Ornek: failed (exception)](res/src/io_fstream15.cpp)  


## Formatsiz I/O Islemleri

<!-- TODO Burayi cpprefden duzenle -->

| stream         | C function |
| -------------- | ---------- |
| ostream::put   | fputc      |
| ostream::write | fwrite     |
| istream::get   | fgetc      |
| istream::read  | fread      |
| istream::seekg | fseek      |
| ostream::seekp | fseek      |
| istream::tellg | ftell      |
| ostream::tellp | ftell      |
| -------------- | ---------- |

* `seekg`/`tellg` *(g: get anlaminda)* fonksiyonlari `istream`, `seekp`/`tellp` *(p:put anlaminda)* fonksiyonlari `ostream` siniflarinda bulunmaktadir.

**`ios::seekdir` enumaratorleri**  
```
ios::beg
ios::end
ios::cur
```
* ileri icin pozitif, geri icin negatif deger verilmelidir.

**Ornek**
```C++
ifs.seekg(1000, ios:beg);   // dosya basindan itibaren 1000. byte
ifs.seekg(-1000, ios::cur); // bulundugu yerden 1000 byte geri
ifs.seekg(0, ios:cur);      // dosya konum gostericini bulundugu konuma konumlandirma: okumadan yazmaya yazmadan okumaya geciste
```

[Ornek: ios::ate ve tellg](res/src/io_fstream05.cpp)
[Ornek: binary read/write](res/src/io_fstream06.cpp)
[Ornek: binary primes](res/src/io_fstream10.cpp)

<!-- TODO Ders 49 1:51:00 -->
[Ornek: bol/birlestir](res/src/io_fstream11.cpp)

**`istream::gcount()`**  
Son yapilan okumadaki byte sayisi  

[Ornek: writing directly into a vector](res/src/io_fstream12.cpp)
[Ornek: writing directly into a vector](res/src/io_fstream13.cpp)


