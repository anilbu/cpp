# Array

* Dizi turleri eleman sayisi ile birlite ifade edilir.
  ```C++
  int a[10];      // int[10]
  char str[20];   // char[20]
  ```

* C++ dilinde dizi ilklendirilirken `{}` ici bos birikilabilir.
  ```C++
  int a[5] = {};
  ```

* Diziler atanabilir varliklar degildir.
  ```C++
  char str[10] = "ali";
  str = "veli";   // sentaks hatasi
  ```

* `[]` operatoru
  ```C++
  int a[10];
  a[5];  // *(a + 5);
  5[a];  // *(5 + a);
  ```
* Dizide var olmayan bir elemana erisim **UB**dir.

## Array decay
*(array to pointer conversion)*

Bir dizi ismi, bir ifade icinde kullanildiginda, ifade dizinin ilk elemaninin adresine donusur. Bu duruma array decay denilir.

Decay uygulanmayan durumlar:
1. `sizeof` operatorunun operandi
2. `&` adress operatorunun operandi

```C++
int a[10];  // int[10]
a;          // int* (decay oldu)
&a[0];      // int*
```
```C++
auto p1 = a;   // p1 = int*
auto p2 = &a;  // p2 = int*[10]
```

**Ornekler**
Asagidaki ayni isimli bildirimler ozdestir, cunku bir fonksiyonun parametresi array turunden olamayacagi icin decay uygulanmaktadir.
```C++
void f1(int*);
void f1(int []);
```
```C++
void f2(int**);
void f2(int*[]);
```
```C++
void f3(int (*)[10]);
void f3(int [][10]);
```
```C++
void f4(int(*)(int));
void f4(int(int));
```

```C++
const char* p1 = "alican";
const char* p2 = "alican";

if(p1 == p2)    // Unspecified Behavior!
    cout << "dogru" << endl;
else
    cout << "yanlis" << endl;

---- 

char s1[] = "alican";
char s2[] = "alican";

if(s1 == s2)    // Always FALSE
                // cunku s1 ve s2 farkli diziler ve farkli adreslerde olusturulacaklar. String literali ile karistirilmamalidir.
    cout << "dogru" << endl;
else
    cout << "yanlis" << endl;

---- 

std::string s1 = "alican";
std::string s2 = "alican";

// operator==(s1, s2) sonucuna gore
if (s1 == s2) 
    cout << "dogru" << endl;
else
    cout << "yanlis" << endl;
```

