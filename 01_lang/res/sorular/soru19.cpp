/*
    Asagidaki fonksiyon cagrisi sonucu ne yazdirir?
*/


#include <iostream>

template <typename T>
void func(T)
{
    std::cout << "1";
}

template <>
void func(int*)
{
    std::cout << "2";
}

template <typename T>
void func(T*)
{
    std::cout << "3";
}

int main(int argc, char const *argv[])
{
    int* p = nullptr;
    func(p);
}
















































/*
    func(10);       // explicit specialization
    func(0.42);     // non-template function
    func('A');      // primary template
    func("10");     // primary template

*/