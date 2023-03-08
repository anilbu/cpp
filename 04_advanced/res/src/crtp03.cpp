#include <iostream>
#include "nutility.h"

// =============================================================================

template<typename T>
struct equivalence_comparable
{
    const T& derived() const {
        return static_cast<const T&>(*this);
    }
};

template<typename T> 
bool operator==(const equivalence_comparable<T>& a, const equivalence_comparable<T>& b)
{
    return !(a.derived() < b.derived()) && !(b.derived() < a.derived());
}

template<typename T> 
bool operator!=(const equivalence_comparable<T>& a, const equivalence_comparable<T>& b)
{
    return !(a == b);
}

// =============================================================================

class A: public equivalence_comparable<A> {
public:
    A(int _val): m_val{ _val } {}

    bool operator<(const A& other) const
    {
        return m_val < other.m_val;
    }
private:
    int m_val;
};

class B: public equivalence_comparable<B> {
public:
    B(double _val): m_val{ _val } {}

    bool operator<(const B& other) const
    {
        return m_val < other.m_val;
    }
private:
    double m_val;
};

int main(int argc, char const *argv[])
{
    using namespace std;

    A a1{ 10 };
    A a2{ 10 };
    A a3{ 20 };

    std::cout << "(a1 == a2) = " << (a1 == a2) << '\n';
    std::cout << "(a1 == a3) = " << (a1 == a3) << '\n';

}


