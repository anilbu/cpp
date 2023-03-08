#ifndef PERSON_H_
#define PERSON_H_
#include <iostream>
#include <string>
#include <memory>

class Person {
public:
    using SharedPtr = std::shared_ptr<Person>;
    using UniquePtr = std::unique_ptr<Person>;

    Person(): m_name{ "default" }
    {
        std::cout << "Person()\n";
    }

    Person(std::string _name) : m_name{ std::move(_name) }
    {
        std::cout << "Person() name = " << m_name << "\n";
    }

    ~Person()
    {
        std::cout << "~Person() name = " << m_name << "\n";
    }
    
    Person& name(const std::string& _name) {
        m_name = _name;
        return *this;
    }
    
    std::string name() const { return m_name; }
    
    friend std::ostream& operator<<(std::ostream& os, const Person& m)
    {
        return os << m.m_name;
    }

    auto operator<=>(const Person& other) const = default;

    static inline std::unique_ptr<Person> create_person()
    {
        static size_t n = 0;
        return std::make_unique<Person>("person" + std::to_string(n++));
    }
    
private:
    std::string m_name;
};


#endif // Person_H_