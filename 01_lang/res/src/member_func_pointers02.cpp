#include <iostream>
#include <functional>
#include "date.h"

class Myclass {
public:
    int foo(int, int);
    
    int f1(int);
    int f2(int);
    int f3(int);
    int f4(int);
    
    void bar()
    {
        ((*this).*mfp)(12);
        (this->*mfp)(12);
    }
    
private: 
    int (Myclass::*mfp)(int) { &Myclass::f1 };
};

typedef int (Myclass::*MFPTR)(int, int);
using MPTR = int (Myclass::*)(int, int);
using MPTR_ = decltype(&Myclass::foo);