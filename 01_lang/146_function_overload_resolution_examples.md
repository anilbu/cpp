### Viable Function Examples

```C++
// (1)
void func(double*);

func(0);        // viable
func(nullptr);  // viable: nullptr_t turunden pointer turlerine donusum var.
```
```C++
// (2)
void func(bool);

func(nullptr);  // viable degil: nullptr'nin turu nullptr_t.
                // nullptr_t bir pointer turune donusebilirken bool turune donusemez.
int x{};
func(&x);       // viable: Pointer turlerinden bool turune donusum vardir.
```
```C++
// (3)
void func(void *);

int ival{};
double dval{};

func(&ival);    // viable: void*'a donusum var
func(&dval);    // viable: void*'a donusum var
```
```C++
// (4)
void func(int *);

int ival{};
double dval{};
void* vp{};

func(&ival);    // viable
func(&dval);    // viable degil: double* 'dan int*'a impl. donusum yok
func(vp);       // viable degil: void*'dan T*'a impl. donusum yok. (C'de var, C++'da yok)
```
```C++
// (5)
void func(const int *);

int x{};
func(&x);   // viable: T*'dan const T*'a her zaman impl donusum vardir.
```
```C++
// (6)
void func(int *);

const int x{};
func(&x);   // viable degil: const T*'dan T*'a impl donusum yoktur.
```
```C++
// (7)
void func(char *);

func("str");   // viable degil: cunku string literali const char*'a decay olur.
```
```C++
// (8)
enum pos {on, off, hold};
enum class color {yellow, dark_blue};

void f(pos);
void g(color);
void h(int);

f(1);   // viable degil: aritmetik turlerden enum turlerine KESINLIKLE impl. donusum yok!
g(1);   // viable degil: aritmetik turlerden enum turlerine KESINLIKLE impl. donusum yok!

f(color::yellow);   // viable degil: Scoped-enum'dan enum'a impl donusum yok! 
g(off);             // viable degil: Scoped-enum'dan enum'a impl donusum yok! 

h(color::yellow);   // viable degil: scoped-enumdan aritmetik ture impl. donusum yok.
h(off);             // viable: enum'dan aritmetik ture impl donusum var.
```
```C++
// (9)
int x = 10;
f(&x);  // parametreler hangi turden olursa cagri gecerli olur?

void f(int*);
void f(const int*);
void f(void*);
void f(bool);

void f(int* &); // viable mi degil mi? Neden?
                // gecersiz: VALUE CATEGORY
                //  &x -> pr value expr
                //  parametre ise L value ref 
                // 
                //  pr value expr, L value ref'a baglanamaz.
                //  
                //  parametre ya R value ref olmali, yada const L value ref olmali

void f(int* &&); // gecerli
```