
## type cast operator ile tur donusumu
Syntax
```C++
(target_type) expr;
```
Tur donusumunun niyeti dilin araclari ile acikca belirtilemiyor. 

Eski tur donusum operatorunu mumkun oldugunca kullanilmasi tavsiye edilmiyor. Yerine C++'in [yeni operatorleri](060_type_conversions.md#explicit-type-conversion) kullanilmasi tavsiye edilmektedir.

```C++
int ival = 10;
double dval = 3.14;

double* dptr = (double*) &ival; // legal, ancak dogru degil
*dptr;       // UB!
```

**Tur donusumu gerektiren durumlardan bazilari**

* Iki tamsayi bolumunden bir gercek sayi elde edilmek istenmesi
  ```C++
  (double)i1 / i2;
  ```
* Isaretli turlerde overflow(UB) riski olan durumlarda
  ```C++
  (long long)i1 * i2;
  ```
* Narrowing conversion soz konusu oldugunda kodun amacini daha acik belirtme
  ```C++
  ival = (int)dval; // veri kaybi bilincli olarak yapildiginin belirtilmesi
  ```

* Nesnenin kendisi const degil ancak sozleme bagli (contractual constness) bir const durumu bulunuyor.
  ```C++
  int x = 10;
  const int* ptr = &x;
  
  *ptr = 45;           // syntax hatasi, cunku ptr const int'e isaret eder
  int* p = ptr;        // syntax hatasi, cunku const T*'dan T*'a implicit donusum yok
  int* p = (int*) ptr; // legal, logic olarak x const degil ve niyet belirtilmis
  *p = 56;             // legal
  ```

* Bir nesneyi baska turden bir nesne gibi kullanilmak istenildiginde (`type-punning`)
  ```C++
  float pi = 3.14159;
  uint32_t piAsRawData = *(uint32_t*)&pi;
  ```
  > **DIKKAT!**
  > Adres donusumlerinden bazilari legal, bazilari **UB** olabilir!