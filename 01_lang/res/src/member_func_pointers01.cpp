#include <iostream>
#include <functional>
#include "date.h"

class Myclass
{
public:
    static void s_func(int x)
    {
        std::cout << "Myclass::s_func(int x) x = " << x << '\n';
    }

    void func(int x)
    {
        std::cout << "Myclass::func(int x) x = " << x << '\n';
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        void (*fp1)(int) = Myclass::s_func;
        void (*fp2)(int) = Myclass::s_func;
        fp1(24);

        // void (Myclass::*fp3)(int) = Myclass::func;  // syntax error
        void (Myclass:: * fp4)(int) = &Myclass::func;
    }
    {
        Date mdate{ 21, 6, 1999 };
        
        auto fp = &Date::week_day;
        int (Date:: * fpx)() const = &Date::year_day;
        std::cout << (mdate.*fpx)() << '\n';

        fpx = &Date::month_day;
        std::cout << (mdate.*fpx)() << '\n';

        auto date_ptr = new Date{ 5, 5, 1955 };

        cout << ((*date_ptr).*fpx)() << '\n';
        cout << (date_ptr->*fpx)() << '\n';
    }
}
