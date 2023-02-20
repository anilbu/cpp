/*
    Asagidaki fonksiyon cagrilari gecerli midir? 
    Gecerli ise hangi fonksiyon ne yazdirir?
*/


#include <iostream>

template <typename T>
void func(const T&)
{
    std::cout << "primary template\n";
}

template <>
void func(const int&)
{
    std::cout << "explicit specialization\n";
}

void func(double)
{
    std::cout << "non-template function\n";
}

int main(int argc, char const *argv[])
{
    // func(10);
    // func(0.42);
    // func('A');
    // func("10");
}
















































/*
    func(10);       // explicit specialization
    func(0.42);     // non-template function
    func('A');      // primary template
    func("10");     // primary template

*/