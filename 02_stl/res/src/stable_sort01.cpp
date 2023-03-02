#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
#include <iomanip>
#include "nutility.h"

struct Person {
    Person() = default;
    Person(const std::string& name, int age): m_name{ name }, m_age{ age } {}

    friend std::ostream& operator<<(std::ostream& os, const Person& p) {
        return os << std::setw(20) << p.m_name << ' ' << p.m_age;
    }

    std::string m_name;
    int m_age;
};

Person random_person()
{
    static Irand rage(20, 30);
    return Person{ rname(), rage()};
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<string> svec;

        rfill(svec, 10, [] { return rname() + ' ' + rfname(); });
        print(svec, ", ");

        // sadece isimlere gore siralama yapilsin
        auto sort_name = [](const string& a, const string& b) {
            const auto name_a = a.substr(0, a.find(' '));
            const auto name_b = b.substr(0, b.find(' '));
            return a < b;
        };
        stable_sort(svec.begin(), svec.end(), sort_name);
        print(svec, ", ");
    }
    {
        vector<Person> pvec1;
        rfill(pvec1, 10, random_person);
        sort(pvec1.begin(), pvec1.end(), [](const Person& a, const Person&b) {
            return a.m_name < b.m_name;
        });
        vector<Person> pvec2 = pvec1;
        print(pvec1, "\n");
        
        sort(pvec1.begin(), pvec1.end(), [](const Person& a, const Person&b) {
            return a.m_age < b.m_age;
        });
        print(pvec1, "\n");
        
   
        stable_sort(pvec2.begin(), pvec2.end(), [](const Person& a, const Person&b) {
            return a.m_age < b.m_age;
        });
        print(pvec2, "\n");
        
    }
}
