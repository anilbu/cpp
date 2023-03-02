#include <iostream>

/*
    C++17 ile operator overloading
*/
class Counter
{
public:
    Counter() = default;
    Counter(int val): m_c{ val } {}

    [[nodiscard]] bool operator<(const Counter &other) const
    {
        return m_c < other.m_c;
    }

    bool operator==(const Counter &other) const
    {
        return m_c == other.m_c;
    }

    bool operator!=(const Counter &other) const
    {
        return !(*this == other);
    }

    bool operator>(const Counter &other) const
    {
        return other < *this;
    }

    bool operator>=(const Counter &other) const
    {
        return !(*this < other);
    }

    bool operator<=(const Counter &other) const
    {
        return !(other < *this);
    }

private:
    int m_c{};
};

int main(int argc, char const *argv[])
{
    Counter a(0), b(0), c(10);

    std::cout << "a == b = " << (a == b) << '\n';
    std::cout << "a != b = " << (a != b) << '\n';
    std::cout << "a <  b = " << (a < b) << '\n';
    std::cout << "a <= b = " << (a <= b) << '\n';
    std::cout << "a >  b = " << (a > b) << '\n';
    std::cout << "a >= b = " << (a >= b) << '\n';
    std::cout << "--------------------------------\n";
    std::cout << "a == c = " << (a == c) << '\n';
    std::cout << "a != c = " << (a != c) << '\n';
    std::cout << "a <  c = " << (a < c) << '\n';
    std::cout << "a <= c = " << (a <= c) << '\n';
    std::cout << "a >  c = " << (a > c) << '\n';
    std::cout << "a >= c = " << (a >= c) << '\n';

}
