#include <iostream>
#include "nutility.h"

class String {
public:
    String() {
        std::cout << "String default ctor\n";
    }

    String(const String& other) {
        std::cout << "String copy ctor\n";
    }

    String(String&& other) {
        std::cout << "String move ctor\n";
    }
};

class Person {
public:
    Person(const String& name): m_name{ name }
    {
    }
private:
    String m_name;
};

class PersonMove {
public:
    PersonMove(String name): m_name{ std::move(name) }
    {
    }
private:
    String m_name;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    {
        String s{};
        Person{ s };
    }
    std::cout << "----------------------\n";
    {
        Person{ String{} };
    }
    std::cout << "----------------------\n";
    {
        String s{};
        PersonMove{ s };
    }
    std::cout << "----------------------\n";
    {
        PersonMove{ String{} };
    }
    std::cout << "----------------------\n";
}
