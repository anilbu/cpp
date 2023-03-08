#include "myclass.h"

struct Myclass::pimpl { 
    int a;
    int b;
    int c;
};

// Myclass::pimpl sinifi burada complete type
Myclass::~Myclass() = default;