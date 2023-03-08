## `std::string`

`string` sinifi; yazi islemleri icin ozellestirilmis, bir **dinamik dizi** yoneten standart STL container'dir. Generic programlamaya yonelik bazi uye fonksiyonlara ve nested typelara sahiptir.

C++ Standart kutuphanenin en cok kullanilan siniflarindan biridir.

Bir sinifin iyi tanimlanmis tek bir sorumlulugu olmali, degisecek ise tek bir nedenden dolayi degismelidir. `string` sinifi bu acidan metin islemlerinin fazla olmasi nedeiyle **fat interface**'e sahiptir.

<!--  -->

* `string` sinifi icin container'da tutulan ogeler `char` turundendir.
  ```C++
  std::basic_string<char, std::char_traits<char>, std::allocator<char>> bstr1;
  std::basic_string<char> bstr2;
  std::string str;
  ```
  *Yukarida bildirilen 3 degiskenin turu aynidir.*

* Modern string implementasyonlari, [small buffer optimization](../04_advanced/001_sbo.md#small-buffer-optimization-sbo) uygulanmakta ve kucuk boyutlu string nesneleri icin dinamik bellek alani tahsis edilmemektedir.
  [Ornek](res/src/string/string01.cpp)

* `string` sinifinin bazi uye fonksiyonlari ayrica index bazli overloadlar bulundurur.
--------------

**string literal**  
```C++
"muratcan"
```
* Compile-time'da belirli
* static omurlu
* Immutable *(iceriginin degistirilmesi **UB**)*

**cstring**  
*Null Terminated Byte Stream (NTBS)*  
```C++
char cstr[] = {'a','l','i','e','m','r','e','\0'};
```
* Sonunda `'\0'` yoksa **UB**

**string**  
*An object of `std::string`*
```C++
string { "Merhaba dunya" };
```

**Tipik parametrik yapilar**  
```C++
cstring param                 const char* cstr
data param                    const char* beg, size_t n
fill param                    size_t n, char fill_char
char param                    char c
std::initializer_list         {'a', 'l', 'i'}
range param                   str, str+5
string param                  string
substring param               string, size_t i_begin
                              string, size_t i_begin, size_t n
```

* cstring parametreye, `nullptr` verilmesi halinde **UB**
* cstring parametreye, `\0` ile sonlanmayan bir char dizi verilirse **UB**
* data parameter'da tasma soz konusu ise, **UB**
* cstring fonksiyonlari tipik olarak adres donerken, string sinifi index doner.

--------------

* `string::size_type`: isaretsiz bir tam sayi turu
  ```C++
  string str;
  size_t idx = str.size();
  string::size_type idx = str.size()
  ```
  Asagidaki parametreler ifade edilirken `size_t` turu kullanilmaktadir:
  * Index ifade eden
  * Uzunluk ifade eden
  * Tane/adet ifade eden

<!-- ### Member Types -->


### Member Functions
#### Ctors

```C++
string();                                            // (1) Default ctor 
string(const string&);                               // (2) Copy ctor
string(string&&);                                    // (3) Move ctor
string(const char*);                                 // (4) cstring ctor
string(const char* beg, size_t n);                   // (5) data ctor

template<typename InputIterator>
string(InputIterator beg, InputIterator end);        // (6) range ctor
string(initializer_list<char>);                      // (7) initializer_list ctor
string(size_t n, char c);                            // (8) fill ctor
string(const string & s, size_t pos);                // (9) substring ctor
string(const string & s, size_t pos, size_t n);      // (10)
```
[Ornek: Ctors](res/src//string/string_ctors.cpp)
* (4) `explicit` degildir.
* (5) `n` parametresi out of range (`'\0'`'dan sonrasi) ise **UB** olusur.
* (7) Kume parantezi (uniform) ile ctor kullanildiginda `initializer_list` parametreli bir ctor digerlerinden oncelikli olarak secilir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  string s1(49, 'A');       // 49 adet 'A'
  string s2{ 49, 'A' };     // AA
  std::cout << "s1 = " << s1 << '\n';   // prints 49 adet 'A'
  std::cout << "s2 = " << s2 << '\n';   // prints AA
  ```
  </details>
  <!--  -->
* (9-10) `pos` index parametresi out of range ise **exception** gonderilir.
* (10) Normalde uzunluk bilgisi out of range oldugunda UB olmasi beklenir. Ancak, burada davranis well-defined'dir ve **geriye kalanlarin tumu** anlamina gelmektedir.

> :warning: 
> `string` sinifinin `char` parametreli bir ctor'u bulunmamaktadir.

#### Iterators 
`begin()` `end()`  `cbegin()` `cend()`  `rbegin()` `rend()`  `crbegin()` `crend()` 

> :warning: 
> `string` sinifinin bazi uye fonksiyonlari **index** parametresi kullanirken, bazi uye fonksiyonlari **iterator** kullanmaktadir.


<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{"merhaba dunya"};

for(auto iter = str.begin(); iter != str.end(); ++iter) {
  char& c = *iter;
  // ...
}

for(auto& c : str) {
  // ...
}
```
</details>
<!--  -->


#### Capacity
##### `string::size`/`string::length`
```C++
size_t string::size() const noexcept;
size_t string::length() const noexcept
``` 
Returns the number of characters in the string, not including any
null-termination.  
`size` fonksiyonu STL Containerlarin ortak interface'ine uygunluk icin bulunmaktadir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s{ "levent ercan" };
auto len = s.length();
std::cout << "s.length() = " << s.length() << '\n';
std::cout << "s.size() = " << s.size() << '\n';
```
</details>
<!--  -->

##### `string::capacity`
```C++
size_t string::capacity() const noexcept;
```
Returns the total number of characters that the %string can hold
before needing to allocate more memory.

> :warning: 
> Reallocation yapilmasi, daha onceden kullanilan pointerlari invalidate eder!

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s { "necati ergin" };
auto cap = s.capacity();
int alloc_cnt{};

for(;;) { 
s.push_back();
if(s.capacity() > cap) { 
    cout << ++alloc_cnt << " size = " << s.size() << " capacity = " <<  s.capacity() << '\n';
    (void) getchar();
    cap = s.capacity();
}
}
```
</details>
<!--  -->


##### `string::max_size`
```C++
size_t string::max_size() const noexcept;
```
Returns the size() of the largest possible %string.  
Tum konternerlarin `max_size` isimli bir fonksiyonu bulunmaktadir. 

##### `string::npos`
```C++
static const std::size_t std::string::npos;
```

* `string::size_type` turunun en buyuk degeridir.
* Arama fonksiyonlari basarisiz oldugunda donulen deger olarak kullanilir.
  
  string class'i arama fonksiyonlari pointer yerine index dondurmesi nedeniyle nullptr donemez. Ayrica `string::npos` degeri bir string icerisinde out-of-range olacagi icin gecerli bir index olamaz. Bu nedenle arama fonksiyonlari `nullptr` yerine `string::npos` degeri doner.
  
  ```C++
  string str{ "nihatuygar" };
  auto idx1 = str.find('u');   // returns 5
  auto idx2 = str.find('k');   // returns string::npos
  ```

* Geriye kalan karakterlerin hepsi anlaminda kullanilabilir.

##### `string::empty`
```C++
bool string::empty() const noexcept;
```

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s{ "levent ercan" };
while(!s.empty()) { 
  cout << s << '\n';
  s.pop_back();
}
```
</details>
<!--  -->

##### `string::resize()`
```C++
void string::resize(size_t __n);
void string::resize(size_t __n, char __c);
```
* resize ekleme yaparken varsayilan olarak `'\0'` ekler.
<!-- TODO: * resize silme yaparken -->
  
<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{"mustafa"};

std::cout << "str.size() = " << str.size() << '\n'; // str.size() = 7

str.resize(100); // size 100 olana kadar sondan '\0' ekleme yapilir 

std::cout << "str.size() = " << str.size() << '\n'; // str.size() = 100
str.resize(5);
std::cout << "str = " << str << '\n'; // str = musta

str.resize(10, '!');
std::cout << "str = " << str << '\n'; // str = musta!!!!!
```
</details>
<!--  -->


##### `string::reserve()` ve `string::shrink_to_fit()`
```C++

```
Capacity'i arttirararak reserve eder. `size`'i degistirmez. Kapasiteyi reserve edilmesi, `operator[]` icin range'i arttirmaz.

* Kapasite otomatik olarak buyur, ancak otomatik olarak kuculmez. 
* Kullanilmayan kapasitenin iade edilmesi icin `shrink_to_fit()` cagrilir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s(300'000, 'a');
std::cout << "s.size() = " << s.size() << '\n';         // s.size() = 300000
std::cout << "s.capacity() = " << s.capacity() << '\n'; // s.capacity() = 300000

s.erase(1);

std::cout << "s.size() = " << s.size() << '\n';         // s.size() = 1
std::cout << "s.capacity() = " << s.capacity() << '\n'; // s.capacity() = 300000

s.shrink_to_fit();  

std::cout << "s.size() = " << s.size() << '\n';         // s.size() = 1
std::cout << "s.capacity() = " << s.capacity() << '\n'; // s.capacity() = 15
```
</details>
<!--  -->



#### Element Access
##### `string::operator[]` ve `string::at()`
```C++
char& string::operator[](size_t __pos);
const char& string::operator[](size_t __pos) const;

char& string::at(size_t __n);
const char& string::at(size_t __n) const;
```

* `operator[]` fonksiyonu gecersiz index kullanilmasi durumunda **UB**dir.  
  index degeri `size()` ile sinirlidir, capacity ile degil.
* `at()` fonksiyonu gecersiz index kullanilmasi durumunda `std::out_of_range` turunden **exception** gonderir.
  
* Okuma amacli olarak bir string'in karakter uzunlugundan bir fazlasi kullanilir ise yazinin sonunda `'\0'` olsa da olmasa da tanimsiz davranis degildir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{"mert"};
str[0] = 's';
str[3] = 'a';
std::cout << "str = " << str << '\n'; // str = sera

// out of range access
std::cout << "str[20] = " << str[20] << '\n'; // UB!

// str.size() + 1 degerine erisilirsa derleyici '\0' donmek durumundadir.
// Bu karaktere atama yapilmasi UB'dir
std::cout << "str[4] = " << str[4] << '\n';   // gecerli
str[4] = 'A';                                 // UB

try
{
  string str{"mert"};
  auto c = str[20];       // UB ancak exception throw edilmez
  auto d = str.at(20);    // std::out_of_range exception throw edilir
}
catch (const std::exception &e)
{
  std::cerr << e.what() << '\n';
}
```
</details>
<!--  -->

##### `string::front()` ve `string::back()`
```C++
char& string::front() noexcept
const char& string::front() const noexcept;

char& string::back() noexcept;
const char& string::back() const noexcept;
```
Container'daki ilk ve son ogeye erisim amaci ile kullanilir.

* Bos bir string ile kullanimi **UB**dir.

#### Modifiers

##### `string::operator=`
```C++
string& string::operator=(const string &__str);
string& string::operator=(string &&__str) noexcept(true);

string& string::operator=(char c);
string& string::operator=(const char *__s);
string& string::operator=(std::initializer_list<char> __l);
```

* `operator=` fonksiyonu copy ve move semantiklerini destekmektedir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s;

string str{"murathan"};
s = str;              // copy assignment
s = std::move(str);   // move assignment
s = string{ "ata" };  // move assignment cunku string{} ifadesi rvalue expr.
s = '+';              // char (char ctor yok ancak assignment var)
s = {'a', 'k'};       // initializer_list
s = "tekin";          // const char* 
```
</details>
<!--  -->



##### `string::assign()`
```C++
string& string::assign(const string& __str);
string& string::assign(string&& __str) noexcept(true);
string& string::assign(const char* __s);
string& string::assign(const char* __s, size_t __n);
string& string::assign(size_t __n, char __c);
string& string::assign(std::initializer_list<char> __l);
string& string::assign(const string& __str, size_t __pos, size_t __n = string::npos);

template<typename InputIterator>
string& string::assign(InputIterator __first, InputIterator __last);
```

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s;
string str{ "mustafa" };
char a[] = "can ahmet kahraman";

s.assign(10, 'A');        // fill assign
s.assign(a + 4, a + 9);   // range assign
s.assign(a + 13, 4);      // data assign
s.assign(str, 4);         // substring assign 
                          // 4. indexden baslayarak geri kalanlarin hepsi
s.assign(str, 1, 4);      // 1. index'den baslayarak 4 karakter
```
</details>
<!--  -->

##### `string::push_back()`, `string::operator+=` ve `string::append()`
```C++
void string::push_back(char __c);

string& string::operator+=(char __c);
string& string::operator+=(std::initializer_list<char> __l);
string& string::operator+=(const char* __s);
string& string::operator+=(const string &__str);
```

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s{"ali"};

s.push_back('m');         // s = "alim"
s += 'm';                 // s = "alimm"
s += "can";               // cstring param: s = "alimmcan"
s += {'o', 'g', 'l', 'u'};// initializer_list param: s = "alimmcanoglu"

s.append(10, 'A');        // fill append
s.append(a + 4, a + 9);   // range append
s.append(a + 13, 4);      // data append
s.append(str, 4);         // substring append
                        // 4. indexden baslayarak geri kalanlarin hepsi
s.append(str, 1, 4);      // 1. index'den baslayarak 4 karakter
```
</details>
<!--  -->

##### `string::insert()`
```C++

```
* Ekleme islemleri sondan yapilirken constant *O(1)* iken, sondan yapilmadiginda lineer *O(n)* dir.
* insert fonksiyonlarinin ilk parametresi index olan overloadlari bulunur.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{ "mustafa" };
char buf[] = "alican";

str.insert(str.begin(), '!');
std::cout << str << '\n';     // prints "mustafa!"

str.insert(str.begin(), 5, 'A');
std::cout << str << '\n';     // prints "mustafa!AAAAA"

str.insert(str.begin(), {'a', 'b', 'c'});
std::cout << str << '\n';     // prints "mustafa!AAAAAabc"

str.insert(str.begin(), buf, buf + 3);
std::cout << str << '\n';     // prints "mustafa!AAAAAabcali"
```
</details>
<!--  -->

##### `string::erase()`
```C++
void? string::erase(size_t idx = 0, size_t n = string::npos);
```

* `erase` fonksiyonlarinin ilk parametresi index olan overloadlari bulunur.
* Bir container erase fonksiyonuna bir iterator alir, yada bir range alir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{ "mustafa" };
str.erase(str.begin() + 3);
str.erase(str.begin(), str.begin() + 3);
str.erase(str.begin(), str.end());
str.erase(str.begin() + 1, str.end() - 1);
```
</details>
<!--  -->

Bir `string`'in tamaminin silinmesi icin asagidakilerden biri kullanilabilir.
```C++
str.erase(str.begin(), str.end());
str.erase(0, string::npos);
str.erase();
str.clear();
str.resize(0);
str = "";
str = {};
str = string{};
```

##### `string::swap`
```C++
void std::string::swap(std::string &__s) noexcept;
```
Sadece pointer'larin takas edildigi cagridir. (move gibi)

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string s1(100'000, 'a');
string s2(200'000, 'b');
```
Iki tane buyuk string'in yer degistirmesi istendiginde asagidaki kod orneginde 3 adet kopyalama islemi gerceklesmektedir. Bunu yapmayin!
```C++
auto temp = s1; // copy ctor
s1 = s2;        // copy assignment
s2 = temp;      // copy assignment
```

Ustteki yerine pointer adreslerini yer degistirmek cok daha az maliyetli bir islemdir.

```C++
s1.swap(s2);
// yada
swap(s1, s2);
```
</details>
<!--  -->



##### `string::replace`
```C++
string& replace (size_t pos, size_t len, const string& str);
string& replace (const_iterator i1, const_iterator i2, const string& str);

string& replace (size_t pos, size_t len, const string& str, size_t subpos, size_t sublen = string::npos);

string& replace (size_t pos, size_t len, const char* s);
string& replace (const_iterator i1, const_iterator i2, const char* s);

string& replace (size_t pos, size_t len, const char* s, size_t n);
string& replace (const_iterator i1, const_iterator i2, const char* s, size_t n);

string& replace (size_t pos, size_t len, size_t n, char c);
string& replace (const_iterator i1, const_iterator i2, size_t n, char c);

template <class InputIterator>
string& replace (const_iterator i1, const_iterator i2, InputIterator first, InputIterator last);

string& replace (const_iterator i1, const_iterator i2, initializer_list<char> il);
```
* Yazinin bir kismini baska bir varlik ile degistirilmesi icin kullanilir.
* Hem iterator hemde index interface ile islem yapilabilir.
* ilk parametreler hangi substr'in degistirilecegini belirtir.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{ "tolgahan" };

// 2'den 4'e sil, ayni yere XYZ ekle
str.replace(2, 4, "XYZ");   // str = toXYZan
str.replace(2, 4, {'x', 'y', 'z'});   // str = toxyzan
str.replace(2, 4, 5, 'i');  // str = toiiiiian
```
</details>
<!--  -->



#### String operations

##### `string::c_str()` ve `string::data()`
```C++
const char* string::c_str() const noexcept;

char* string::data() noexcept;
const char* string::data() const noexcept;
```
`c_str` fonksiyonu string nesnesini bir `const char*` olarak cstring'e donusumunu yapar.  
Do not modify or dire things may happen.

`data` fonksiyonu heapde tutulan array'i `char*` olarak doner.
Modifying the characters in the sequence is allowed.

* cstring'den string'e ortulu donusum var ancak string'den cstring'e yoktur.
* `data` fonksiyonu

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
void func1(const char* p);
void func2(const char* p, size_t n);

string str{ "mustafa" };
func1(str.c_str());
func2(str.c_str(), str.size());

// hepsi yazinin baslangic adresidir:
char* p1 = &str[0];
char* p2 = &*str.begin();
char* p3 = str.data();
const char* p4 = str.c_str();
```
</details>
<!--  -->


##### `std::substr`
```C++
string string::substr(size_t __pos = string::npos, size_t __n = string::npos) const;
```
> :warning: 
> `substr` kopyalama yaparak **yeni bir string nesnesi** olusturur. Bu nedenle substring operasyonlari maliyeti yuksek bir operasyondur.
  
<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{ "murathan" };
cout << "|" << str.substr(3, 5) << "|\n";
```
</details>
<!--  -->

##### Arama islemleri
`find` ismi ile baslayan tum arama fonksiyonlari icin asagidakiler gecerlidir:
* Basarisiz oldugunda `string::npos` degeri doner.
* Parametrelerinde baslangic index'i bulunur.

Arama fonksiyonlari: 
| Fonksiyon            | Aciklama                                                          |
| -------------------- | ----------------------------------------------------------------- |
| `find`               | Bastan sona dogru arama                                           |
| `rfind`              | Sondan basa dogru arama                                           |
| `find_first_of`      | Bir karakter grubundaki karakterlerden ilkinin konumu             |
| `find_first_not_of`  | Bir karakter grubundaki bulunmayan karakterlerden ilkinin         | konumu         |
| `find_last_of`       | Bir karakter grubundaki karakterlerden sondan basa ilkinin konumu |
| `find_last_not_of`   | Bir karakter grubundaki bulunmayan karakterlerden sondan basa     | ilkinin konumu |
| `starts_with`[C++20] |                                                                   |
| `ends_with`[C++20]   |                                                                   |
| `contains`[C++23]    | Bir string icerisinde baska bir string tam olarak bulunuyor mu    | sinamasi.      |

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{"ben kayseriye gidiyorum"};

if(const auto idx = str.find('k'); idx != string::npos) { 
  cout << "bulundu idx = " << idx << '\n';
  str[idx] = '!';
  std::cout << "str = " << str << '\n';
}
else{
  cout << "bulunamadi\n";
}
```
</details>
<!--  -->

##### Karsilastirma islemleri
```C++
s1 == s2
s1 == "alican"
s1 > s2
vb...
```
Karsilastirma islemlerini direkt olarak karsilastirma operatorleri ile yapmak mumkun.

> :warning: 
> [C++20] standartlarina kadar string sinifinin karsilastirma operatorleri global operator tanimlariydi. C++20 standardi ile `operator<=>` (three-way comparison/spaceship operator) eklenmesi ile bu operator kullanilarak implementasyon yapilmistir.

###### `string::compare`
```C++
int string::compare(const string &__str) const;
int string::compare(const char *__s) const noexcept;
int string::compare(size_t __pos, size_t __n1, const char *__s) const;
int string::compare(size_t __pos, size_t __n1, const char *__s, size_t __n2) const;
int string::compare(size_t __pos1, size_t __n1, const string &__str, size_t __pos2, size_t __n2 = string::npos) const;
```
* compare fonksiyonu std::strcmp gibi karsilastirma sonucunu bir int deger olarak doner.

  > **cstring comparison**
  >
  > `int std::strcmp(const char* p1, const char* p2);`
  > 
  > Eger
  >   * p1 > p2 ise pozitif bir deger
  >   * p1 < p2 ise negatif bir deger
  >   * p1 == p2 ise 0 degeri
  > 
  > doner.

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str{ "necatiergin" };
string s{ "necatiergin" };
int res;
res = str.compare("ali");
res = str.compare(s, 3, 5);
```
</details>
<!--  -->


#### Donusum Fonksiyonlari

##### `stoX()`
```C++
inline int stoi(const string &__str, size_t *__idx = nullptr, int __base = 10)
```

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
string str { "874325mehmet" };

int ival;
ival = stoi(str);   // ival = 874325
ival = stoi(str, nullptr, 10);

size_t idx; // kullanilmayan ilk karakterin indexi
ival = stoi(str, &idx); // ival = 874325, idx = 6

ival = stoi(str, nullptr, 16); // ival = 8864549, cunku 16'lik sayi sistemi

```
</details>
<!--  -->

> String Class in Detail: The C++ STL, p.693  
> Ozel durumlari ile birlikte detayli aciklamalar

##### `string::to_string()`
```C++
inline string to_string(int __val) noexcept;
```

<details>
<summary><b>Ornek</b> (Click to expand)</summary>

```C++
double dval = 566.123;
string s = to_string(dval);

int ival = 123;
auto fname = "necati" + to_string(ival) + ".jpeg";
```
</details>
<!--  -->


### Non-member functions

#### `operator+`
```C++

```
* Bir string ile baska bir string'i `operator+`'nin operandlari yapilabilir.
* Her bir toplama islemi icin sonuc olarak yeni bir string uretilir.

```C++
string s1, s2;
cout << s1 + s2 << "\n";
cout << "ali" + s1 + "can" << "\n";
```
> :warning: Iki cstring'i `operator+` ile toplayamazsiniz.

### std::string ile ilgili onemli notlar

* Tutulan karakterler ayni olsa dahi iki string nesnesi farkli nesnelerdir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  string s1{"test"};
  string s2{"test"};
  
  // copy on write degildir!
  std::cout << "static_cast<void*>(s1.data()) = " << static_cast<void*>(s1.data()) << '\n';
  std::cout << "static_cast<void*>(s2.data()) = " << static_cast<void*>(s2.data()) << '\n';
  ```
  cstring icin benzer durum **unspecified behavior**dur.
  ```C++
  const char* p1 = "test2";
  const char* p2 = "test2";
  
  if(p1 == p2) { 
      cout << "ayni adres\n";
  }
  else{ 
      cout << "farkli adres\n";
  }
    
  ```
  </details>
  <!--  -->
  
  
* string nesnelerinde *[copy-on-write](999_kavramlar.md#copy-on-write)* uygulanmadigi standartlar ile garanti altindadir.
  <details>
  <summary><b>Ornek</b> (Click to expand)</summary>
  
  ```C++
  string s1{"test"};
  string s2{"test"};
  
  std::cout << "static_cast<void*>(s1.data()) = " << static_cast<void *>(s1.data()) << '\n';
  std::cout << "static_cast<void*>(s2.data()) = " << static_cast<void *>(s2.data()) << '\n';
  ```
  </details>
  <!--  -->
  
  
<!-- 
TODO: Detaylandir

**`char[]` vs `string`**  
* `char[]` statik, `std::string` dinamik. 



> ### [Homework: string](https://github.com/necatiergin/cpp_kursu_odevleri/std_string/)
> ### [Homework: Date sinifi impl.](https://github.com/necatiergin/cpp_kursu_odevleri/date_odevi.md/)
-->


