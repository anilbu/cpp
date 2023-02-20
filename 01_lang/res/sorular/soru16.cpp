/*
    Asagidaki template derlendiginde hangi satirlarda syntax hatasi verir?
*/

template <typename T>
void func(T x)
{
    foo(x);
    bar();
    ++y;
}




























































/*
    foo(x); // gecerli: Cunku T turune bagli olarak foo ismi ADL ile bulunabilir bir isim olabilir.
    bar();  // gecersiz: syntax error
    ++y;    // gecersiz: syntax error
*/