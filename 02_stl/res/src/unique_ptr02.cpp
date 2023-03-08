#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"
#include "date.h"
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        unique_ptr<Person> uptr1{};

        std::cout << "uptr1.operator bool() = " << uptr1.operator bool() << '\n';
        std::cout << "(uptr1 == nullptr) = " << (uptr1 == nullptr) << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Person> uptr2{ new Person };

        std::cout << "uptr2.operator bool() = " << uptr2.operator bool() << '\n';
        std::cout << "(uptr2 == nullptr) = " << (uptr2 == nullptr) << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Date> dptr{ new Date{ 21, 1, 2023 }};

        std::cout << "*dptr = " << *dptr << '\n';
        std::cout << "dptr->month_day() = " << dptr->month_day() << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Person> uptr { new Person{ "obj1" } };
        std::cout << "uptr = " << (uptr ? "dolu" : "bos") << '\n';

        // auto upx = uptr;    // copy ctor deleted

        // unique_ptr<Person> upx;
        // upx = uptr;         // copy assignment deleted

        auto upx{ std::move(uptr) }; // move ctor
        std::cout << "uptr = " << (uptr ? "dolu" : "bos") << '\n';
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';

        std::cout << "Bu noktada obj1 destroy edilmedi, sadece sahibi degisti.\n";
        // (void) getchar();
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Person> upx { new Person{ "obj1" } };
        unique_ptr<Person> upy { new Person{ "obj2" } };

        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        std::cout << "upy = " << (upy ? "dolu" : "bos") << '\n';
        
        upx = std::move(upy);
        std::cout << "obj1 yerine obj2 atandigi icin obj1 destroy edildi.\n";

        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        std::cout << "upy = " << (upy ? "dolu" : "bos") << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Person> upx { new Person{ "obj1" } };
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        
        Person* p = upx.get();
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        std::cout << "*p = " << *p << '\n';
    }
    std::cout << "---------------------\n";
    {
        unique_ptr<Person> upx { new Person{ "obj1" } };
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        
        Person* p = upx.get();
        
        // delete p; // UB! 
        // std::cout << "*upx = " << *upx << '\n'; // UB! upx dangling pointer: upx'in nesnenin delete edildiginden haberi yok
    }
}
