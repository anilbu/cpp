#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
#include <memory>
#include <string>
#include "nutility.h"

class Person
{
public:
    Person(std::string fname, std::string lname)
    : m_fname{ std::move(fname) }, m_lname{ std::move(lname) } {
        std::cout << *this << " is being created this = " << this <<"\n";
    }
    
    ~Person()
    {
        std::cout << *this << " is being destroyed this = " << this << '\n';
    }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& p)
    {
        return os << p.m_fname << " " << p.m_lname;
    }
    
    auto operator<=>(const Person& p) const = default;
    
    Person& set_name(const std::string& name)
    {
        m_fname = name;
        return *this;
    }
    
    static Person create_person()
    {
        return Person{rname(), rfname()};
    }
    
    // tamamla
private:
    std::string m_fname;
    std::string m_lname;
};

#endif // PERSON_H_