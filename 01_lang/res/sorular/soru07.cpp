#include <iostream>

int foo(int);

int main(int argc, char const *argv[])
{
    // auto &x = &foo;          // (1)
    
    // auto p = foo;
    // auto x = &p;             // (2)
}































































/*
cevap:

 (1) sentaks hatasi: must be an lvalue
 
 (2) p bir pointer to function, x ise pointer to function pointer
     p = int(*)(int)
     x = int(**)(int)
 */
