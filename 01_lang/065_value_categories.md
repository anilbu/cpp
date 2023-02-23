# Value Categories

Her bir ifadenin bir **data type**'i ve bir **value category**'si bulunmaktadir.
> **DIKKAT!**
> Modern C++ ogrenenlerin en sik yaptigi hatalardan biri data type ile value category'i karistirmasidir.
> 
> Bir **<ins>IFADENIN</ins>** value kategorisi olur, bir degiskenin value kategorisinden bahsedilemez. Bir degiskenin data type (declaration type)'i olur.


**Primary value categories**
* PR value
* L value
* X value

**Secondary value categories**
* R value = PR value $\cup$ X value
* GL value = L value $\cup$ X value

<!--  -->

* Bir ismin olusturdugu ifade her zaman lvalue expressiondir. Cunku derleyici arkaplanda bir gecici nesne olusturur.
  ```C++
  int &&rr = 10;
  rr  // turu int&& olan bir lvalue expr
  ```

-----

**Ornekler**
```C++
20  // prvalue expr
```
```C++
int x = 5;
x   // lvalue expr
```
```C++
int &r = x;
r   // lvalue expr
```

```C++
int x = 10;

&x;                     // data type: int*

int* &r = &x;           // sentaks hatasi: cunku &x ifadesi bir rvalue expr ve lvalue ref'e baglanamaz.
int* &&rr = &x;         // gecerli: cunku &x rvalue expr. ve rvalue ref'e baglanabilir.

const int* &r = &x;     // sentaks hatasi: constluk verilen ref degil, pointerin isaret ettigi int turu
int* const &r = &x;     // gecerli: cunku rvalue expr, const lvalue ref'e baglanabilir.

using iptr = int*;    
const  iptr& r = &x;    // gecerli: cunku const iptr == int* const (top-level const)
```
