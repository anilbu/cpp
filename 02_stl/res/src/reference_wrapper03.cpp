#include <iostream>
#include <functional>
#include <random>

// Bir kutuphaneden gelen ref parametresi olmayan generic bir fonksiyon oldugunu varsayin
template<typename GenFunc>
void func(GenFunc x)
{
    auto val = x();
    std::cout << "val = " << val << '\n';
}

template<typename T>
void foo(T x)
{
    x.get() << "foo()\n";
}

template<typename T>
void bar(T x)
{
    x += 20;
}


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        cout << "sizeof(std::mt19937) = " << sizeof(mt19937) << '\n';

        mt19937 eng;

        // reference parametresi olmayan bir fonksiyona ref gonderimi
        func(ref(eng));
    }
    {
        // foo(cout);  // sentaks hatasi: ostream sinifi kopyalamaya karsi kapali
        foo(ref(cout));
    }
    {
        int a = 10;
        
        int& aref = a;
        bar(aref);
        std::cout << "a = " << a << '\n';
        
        bar<int&>(a);
        std::cout << "a = " << a << '\n';
        
        bar(ref(a));
        std::cout << "a = " << a << '\n';
    }
}