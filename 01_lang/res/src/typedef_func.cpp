#include <iostream>
#include <functional>

int f1(int, int);
int f2(int, int);
int f3(int, int);

typedef int (*FPTR)(int, int);
using FPTR_ = int(*)(int, int);     // C++ only
using FPTR__ = decltype(f1);        // C++ only

FPTR foo(FPTR);

int main(int argc, char const *argv[])
{
    // 1. f1'in adresini bir func ptr'inda tutun:
    int(*fp)(int, int) = f1;
    FPTR fp_ = f1;
    
    // 2. fp'nin adresini bir ptr degiskende tutun:
    int(**fpp)(int, int) = &fp;
    FPTR* fpp_ = &fp;
    
    // 3. Elemanlari f1, f2 ve f3 fonksiyonlarinin adresleri olacak ismi fpa olan bir dizi tanimlayin:
    int (*fpa[])(int, int) = {f1, f2, f3};
    FPTR fpa_[] = {f1, f2, f3};
}
