/*
    parametresi olmayan
    geri donus turu int(*)(int) olan bir fonksiyon olusturun
*/

int foo(int);








































































int(*func(void))(int) 
{
    return foo;
}

auto func2(void) -> int(*)(int)
{
    return foo;
}