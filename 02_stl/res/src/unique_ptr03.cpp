#include <iostream>
#include <memory>
#include <string>
#include <algorithm>
#include "nutility.h"
#include "date.h"
#include "person.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        unique_ptr<Person> upx;
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';

        // upx = new Person{"obj1"}; // sentaks hatasi: operator=(T*) yoktur.
        upx.reset(new Person{ "obj1" });
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
    }
    std::cout << "-------------------\n";
    {
        unique_ptr<Person> upx{new Person{ "obj1" }};
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';

        upx.reset();                    // alternatif
        upx.reset(nullptr);             // alternatif
        upx = nullptr;                  // alternatif
        upx = unique_ptr<Person>{};    // alternatif
        upx = {};                       // alternatif
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
    }
    std::cout << "-------------------\n";
    {
        unique_ptr<Person> upx{new Person{ "obj1" }};
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';

        Person* obj1_ptr = upx.release();
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        std::cout << "*obj1_ptr = " << *obj1_ptr << '\n';

        std::cout << "deleting obj1_ptr\n";
        delete obj1_ptr;
    }
    std::cout << "-------------------\n";
    {
        unique_ptr<Person> upx { new Person("obj1") };
        unique_ptr<Person> upy { upx.release() };
        std::cout << "upx = " << (upx ? "dolu" : "bos") << '\n';
        std::cout << "upy = " << (upy ? "dolu" : "bos") << '\n';
    }
    std::cout << "-------------------\n";
    {
        unique_ptr<Person> upx { new Person("obj1") };
        unique_ptr<Person> upy { new Person("obj2") };
        std::cout << "*upx = " << *upx << '\n';
        std::cout << "*upy = " << *upy << '\n';
        
        upx.swap(upy);
        // swap(upx, upy);
        std::cout << "*upx = " << *upx << '\n';
        std::cout << "*upy = " << *upy << '\n';
    }
    std::cout << "-------------------\n";
    {
        unique_ptr<Person[]> uptr(new Person[3]);
    }
}
