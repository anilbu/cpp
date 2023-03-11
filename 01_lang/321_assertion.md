# Assertion
*Dogrulama/Garanti etme*  

Programin derleme yada calisma zamaninda bir durumun programlama hatalarinin tespiti amaciyla yapilan dogrulanmadir.

## `static_assert`[C++11]
Derleme zamaninda yapilan dogrulamalardir. 

```C++
static_assert(bool-constexpr, message)          // C++11
static_assert(bool-constexpr)                   // C++17
```

* `static_assert` bir keyworddur.  
  *Herhangi bir baslik dosyasinin eklenmesine gerek yoktur.*
* Bir **constexpr** ifade olmalidir.  
  [type_traits](../02_stl/520_type_traits.md#type-traits) ile birlikte kullanilabilir.
  ```C++
  static_assert(sizeof(long) > 4, "long turu 4 bytedan buyuk olmali");
  static_assert(is_pointer_v<T>, "T must be a pointer type");
  static_assert(is_same_v<T, long int> || is_same_v<T, long long int>);
  ```
* `static_assert` diger statementlardan farkli olarak bircok yerde kullanilabilmektedir.  
  > :warning: 
  > Fonksiyon sablonlarinda `static_assert` sadece fonksiyon blogunda kullanilabilmektedir. Dolayisiyla, fonksiyon sablonunun function overload resolution'a girmemesi istenmekteyse, static_assert kullanimi yeterli olmayacaktir.

[Ornek](res/src/static_assert01.cpp)

<details>
<summary><b>static_assert dile eklenmeden once kullanilan teknikler</b> (Click to expand)</summary>

Dizi boyutunun sifir olamamasindan faydalanilabilir.
```C++
int a[sizeof(int) == 4];
typdef int ar[sizeof(int) == 4];
```
> :triangular_flag_on_post: Yan etki olarak bir isim ile dizi tanimi yapilmis oldu.

Yan etkiden kacinmak icin *typedef* bildiriminden faydalanilabilir:
```C++
typedef int ar[sizeof(int) == 4];   // sizeof(int) == 4 degilse sentaks hatasi olusacaktir.
```
</details>
<!--  -->

## `dynamic_assert`
Calisma zamaninda yapilan dogrulamalardir. 

**`assert` makrosu**
aborts the program if the user-specified condition is not true. May be disabled for release builds
```C++
#ifdef NDEBUG
#  define assert(condition) ((void)0)
#else
#  define assert(condition) /*implementation defined*/
#endif
```
The definition of the macro assert depends on another macro, NDEBUG, which is not defined by the standard library.

If NDEBUG is defined as a macro name at the point in the source code where <cassert> or <assert.h> is included, then assert does nothing.

If NDEBUG is not defined, then assert checks if its argument (which must have scalar type) compares equal to zero. If it does, assert outputs implementation-specific diagnostic information on the standard error output and calls std::abort.

```C++
#include <iostream>
// uncomment to disable assert()
// #define NDEBUG
#include <cassert>
 
// Use (void) to silence unused warnings.
#define assertm(exp, msg) assert(((void)msg, exp))
 
int main()
{
    assert(2+2==4);
    std::cout << "Checkpoint #1\n";
 
    assert((void("void helps to avoid 'unused value' warning"), 2*2==4));
    std::cout << "Checkpoint #2\n";
 
    assert((010+010==16) && "Yet another way to add an assert message");
    std::cout << "Checkpoint #3\n";
 
    assertm((2+2)%3==1, "Expect expected");
    std::cout << "Checkpoint #4\n";
 
    assertm(2+2==5, "There are five lights"); // assertion fails
    std::cout << "Execution continues past the last assert\n"; // No
}
```
