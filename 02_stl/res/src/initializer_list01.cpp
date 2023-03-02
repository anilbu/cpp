#include <iostream>
#include <initializer_list>
#include "nutility.h"

void foo(std::initializer_list<int> x) {

}

template<typename T>
void func(T)
{
}


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        initializer_list<int> x{ 1, 3, 5, 7, 9, 11, 13, 15, 17};

        std::cout << "sizeof(x) = " << sizeof(x) << '\n';
        std::cout << "sizeof(void*) = " << sizeof(void*) << '\n';
    }
    {
        initializer_list<int> x{ 1, 3, 5, 7, 9, 11, 13, 15, 17};

        for (auto iter = x.begin(); iter < x.end(); ++iter)
        {
            std::cout << *iter << ", ";
        }
        std::cout << "\n--------------------\n";
        for (auto e : x) {
            std::cout << e << ", ";
        }
        std::cout << "\n--------------------\n";
    }
    {
        foo({ 1, 3, 5 });
        foo({ 1, 3, 5, 7, 9 });
    }
    {
        auto x = { 1,2,3,4,5 };     // x = initializer_list<int>
        auto y{ 10 };               // y = int
        // auto z{ 10, 20 };        // sentaks hatasi
        
        print(x);
        std::cout << "y = " << y << '\n';
    }
    {
        auto x = { 1,2,3,4,5 };     // x = initializer_list<int>
        // func({1,2,3,4,5});       // sentaks hatasi
        func(x);                    // gecerli
    }
    {
        class Nec {
        public:
            Nec(int) {
                std::cout << "Nec(int)\n";
            }

            Nec(int, int) {
                std::cout << "Nec(int, int)\n";
            }

            Nec(std::initializer_list<int>) {
                std::cout << "Nec(std::initializer_list<int>)\n";
            }
        };

        Nec x1(12);         // Nec(int)
        Nec x2(12, 56);     // Nec(int, int)
        Nec x3{ 12 };       // Nec(std::initializer_list<int>)
        Nec x4{ 12, 56 };   // Nec(std::initializer_list<int>)
    }
}
