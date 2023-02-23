/*
    Asagidaki template derlendiginde hangi satirlarda sentaks hatasi verir?
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
    bar();  // gecersiz: sentaks hatasi
    ++y;    // gecersiz: sentaks hatasi
*/