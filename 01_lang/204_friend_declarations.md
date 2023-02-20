## Friend declarations

Normalde bir sinifin private alanlarina client kodlarin erisimi bulunmamaktadir. Ancak C++ dilinde sinifin interface'i sadece public alanindan olusmamaktadir.

`friend` bildirimi sinifin `private` ogelerini **global nesnelere** erisim vermek amaciyla kullanilmaktadir. Burada onemli olan nokta **sinifin kendi kodlarina** friend verilmesidir.

Friend bildirimi ile;

  1. Bir namespace'deki global fonksiyona
  2. Bir sinifin bir uye fonksiyonuna
  3. Bir sinifin tamamina

private alanlarina erisim verilebilir.

* Friend bildirimin sinifin public veya private bolumde yapilmis olmasinin onemi yoktur.
* Sadece bazi private elemanlara erisim icin friend verilemez.  
  *Ya hepsine yada hicbirine, alternatifi olarak **Attorney-client idiomu** kullanilabilir.*
* Friend bildirimleri **iki yonlu degildir**.  
  *A sinifi B sinifina friend bildirimi vermis ise bu B sinifi A sinifina friend erisimi verdigi anlamina gelmiyor.*
* Friend bildirimleri **gecisken degildir**.  
  *A sinifi B sinifina, B sinifi C sinifina friend bildirimi vermis ise bu A sinifi C sinifina friend erisimi verdigi anlamina gelmiyor. Arkadasin arkadasi arkadas olmak zorunda degil.*
* friend bildirimleri **kalitim yoluyla alt siniflara aktarilmaz**.  
  *Dedemin, babamin arkadaslari benim arkadasim degillerdir.*
  
### 1. friend to global function
```C++
class Myclass {
public:
  friend void func1(Myclass);  // belirtilen fonksiyon imzasina private erisim verildi.
private:
  int mx;
  void foo();
};

void func1(Myclass pm) { 
  Myclass m;
  pm.foo();
  m.foo();
  m.mx = 3;
}
```
#### **hidden friend**
Sinifin icinde implicity `inline` olarak tanimi yapilan `friend` fonksiyon sinifin uye fonksiyonu degildir.
```C++
class Myclass {
public:
  friend void func(Myclass pm) {
    pm.foo();
  }
private:
  void foo();
};
```

### 2. friend to a class member
```C++
class Nec {
  public:
    void foo();
};

class Myclass{ 
private:
  friend void Nec::foo();
  void func();
};

void Nec::foo() {
  Myclass x;
  x.foo();
}
```
> **DIKKAT!**
> `friend` verilen sinifin **complete type** olmasi gerekmektedir.  
> *friend declaration yapilan noktada friend verilen uye fonksiyonun isminin gorunebilir olmasi gerekmektedir.*

### 3. friend to a class
```C++
class Myclass{ 
private:
  friend class Nec;
  
  void f1();
};

class Nec{ 
  void foo() {
    Myclass m;
    m.f1();
  }
  
  void bar() {
    Myclass m;
    m.f1();
  }
};
```
