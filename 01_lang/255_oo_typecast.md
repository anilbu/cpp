## Tur donusum operator fonksiyonlarinin overload edilmesi

```C++
class Myclass{
public:
    operator int() const;
    operator int*() const;
    operator int&() const;
    explicit operator double() const;
}

Myclass m;
int ival = m;
```

* Tur donusum operatorleri **unary** operatordur.
* Sadece member function olarak overload edilebilir.
* Tipik olarak **const member function**dir.
* Geri donus turu zaten hedef tur olmasi nedeniyle ayrica belirtilmez.
* `T*` ve `T&` turleri de hedef tur olarak ayrica overload edilebilir.
* [C++11] Tur donusumu operator fonksiyonlari ile otomatik donusum yapilmamasi icin `explicit` keywordu kullanilabilir.

> **Hatirlatma**  
> 
> * Eger bir donusum implicit olarak;
> 
>   *SC* + *UDC*   
>   *UDC* + *SC*  
> 
>   olarak yapilabiliyor ise derleyici bu donusumu yapmak **zorunda**dir.
> 
> * Eger bir donusum sadece  
>       *UDC* + *UDC*  
>   olarak yapilabiliyorsa derleyici bu donusumu yapmak **zorunda degil**dir.
> 
> *SC*: standart conversion  
> *UDC*: user-defined conversion  
> 

```C++
class Nec {
    
};

class Myclass {
public:
    operator int() const;
    operator double() const;
    operator int*() const;
    operator int&() const;
    explicit operator Nec() const {
        return Nec{};
    }
};

Myclass m;
int x = m;  // int x = m.operator int();

Nec n1 = m;                   // syntax hatasi: explicit donusum yapilmali
Nec n2 = static_cast<Nec>(m); // legal

double dval = m;  // once Myclass'dan int'e, sonra int'ten double'a donusum gerceklesir.
```

[Ornek: Counter sinifi](res/src/16_typecast_overload.cpp)

```C++
class Counter {
public:
    explicit Counter(int);
    ...
    operator int() const;
}
```
```C++
Counter cnt{ 310 };
    
int ival = cnt;
double dval1 = cnt;                      // syntax error: explicit
double dval2 = static_cast<double>(cnt); // gecerli

// Eger Counter::operator int() overload edilmis ise:
auto val1 = cnt;     // auto = Counter
auto val2 = +cnt;    // gecerli: +(cnt.operator int()) ve auto = int olacak.

// Eger Counter::operator int() overload edilmemis ise:
auto val3 = cnt;     // auto = int, cunku copy ctor calisacak
auto val4 = +cnt;    // syntax error: Counter nesnesinin isaret operatoru  yok
```
```C++
Counter cnt1 {10};
Counter cnt2 {20};

// Eger Counter::operator int() overload edilmemis ise:
cnt1 + cnt2;     // syntax error: Counter'un toplama operatoru yok

// Eger Counter::operator int() overload edilmis ise:
cnt1 + cnt2;     // gecerli: cnt1.operator int() + cnt2.operator int()
```
* Sinifin `bool` turune yada `bool`'a donusebilen bir ture donusumu varsa asagidaki ifadeler gecerli olacaktir.
  ```C++
  class Nec {
      operator int() const;
  };
  
  // operator int() overload edilmemis ise
  Nec nec1, nec2;
  if(nec1);       // syntax error
  !nec1;          // syntax error
  nec1 && nec2;   // syntax error
  nec1 || nec2;   // syntax error
  nec1 ? 10 : 20; // syntax error
  
  // operator int() overload edilmis ise
  Nec nec1, nec2;
  if(nec1);       // gecerli
  !nec1;          // gecerli
  nec1 && nec2;   // gecerli
  nec1 || nec2;   // gecerli
  nec1 ? 10 : 20; // gecerli
  ```
  
* `operator bool()` fonksiyonu explicit olsa dahi boolean context'de kullanildiginda ortulu donusum yapilir.  
  *operator bool() fonksiyonunun explicit yapilmasi tavsiye edilir.*
  ```C++
  class Nec {
      explicit operator bool() const;
  };
  
  // operator bool() explicit degil ise
  Nec nec1, nec2;
  int x = nec1;   // gecerli
  if(nec1);       // gecerli
  !nec1;          // gecerli
  nec1 && nec2;   // gecerli
  nec1 || nec2;   // gecerli
  nec1 ? 10 : 20; // gecerli
  
  // operator bool() explicit ise
  Nec nec1, nec2;
  int x = nec1;   // syntax error: static_cast yapilmali
  if(nec1);       // gecerli
  !nec1;          // gecerli
  nec1 && nec2;   // gecerli
  nec1 || nec2;   // gecerli
  nec1 ? 10 : 20; // gecerli
  ```
  
> **Mulakat Sorusu**  
> Asagidaki programda bir syntax hatasi var midir?  
> Eger yok ise auto turu ve program ciktisi nedir?  
> Eger operator bool explicit olsaydi ne olurdu?
> ```C++
> class Nec {
> public:
>     operator bool() const {
>         return true;
>     }
> };
> 
> int main() {
>     Nec x, y;
>     auto val = x + y;
>     std::cout << "val = " << val << '\n';
> }
> ```
> **Cevap**  
> ```
> val = 2
> ```
> 1. Nec nesnelerinin toplanabilmesi icin derleyici x ve y'ye implicit olarak bool'a donusum uygular. 
> 2. Iki bool degerinin toplanabilmesi icin integral promotion uygulanarak bool degerleri int'e 1 degerini alacak bicimde donusur.
> 3. Eger explicit olsaydi x + y ifadesinde syntax error olusurdu.

```C++
#include <memory>

std::unique_ptr<string> up { new std::string{"ali"}};

int x = up;     // syntax error: operator bool() explicit
if(up)          // gecerli: up.operator bool()
    std::cout << "not empty!\n";
else 
    std::cout << "empty!\n";
```

```C++
int ival;

while (std::cin >> ival)
    cout << ival << '\n';

```
`std::cin.operator>>()`'un geri donus turu `std::istream`'dir, ancak `while(std::cin >> ival)` ifadesi bir boolean context olmasi nedeniyle aslinda `std::cin.operator>>(ival).operator bool()` cagrisi yapildi. Bir stream nesnesin `operator bool()` fonksiyonun streamin state'inde hata olup olmadigini geri doner.

```C++
#include <optional>

// kisinin middle name'i olmayabilir.
std::optional<std::string> get_middle_name(Person);

std::optional<int> op;

if(op)      // op.operator bool()
    std::cout << "dolu\n";
else
    std::cout << "bos\n";
```
```C++
#include <functional>

int x = 10;
std::reference_wrapper r = x;   // r bir sinif nesnesi ancak x'e referans ediyor.
int ival = r;   // legal: r.operator int&()

++r;    // ++(r.operator int&())
```
```C++
enum class Weekday {
  MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY
};

Weekday wd{ Weekday::MONDAY };

++wd;             // syntax error: oper. overl. yok
wd++;             // syntax error: oper. overl. yok
std::cout << wd;  // syntax error: oper. overl. yok

// prefix
Weekday& operator++(Weekday& wd){
  return wd == Weekday.SATURDAY 
      ? Weekday.SUNDAY 
      : static_cast<Weekday>(static_cast<int>(wd) + 1);
}

// postfix
Weekday operator++(Weekday& wd, int) {
  Weekday retval { wd };
  ++wd;
  return retval;
}

std::ostream& operator<<(std::ostream& os, const Weekday& wd)
{
  static constexpr const char* p[] = {
      "MONDAY", "TUESDAY", "WEDNESDAY", "THURSDAY", "FRIDAY", "SATURDAY", "SUNDAY"
  };
  
  return os << p[static_cast<int>(wd)];
}

int ival = wd;    // gecerli: operator int(wd)
++wd;             // gecerli: operator++(wd)
wd++;             // gecerli: operator++(wd, 0)
std::cout << wd;  // gecerli: operator<<(std::cout, wd)
```