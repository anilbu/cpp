#ifndef COUNTER_H
#define COUNTER_H

#include <ostream>

namespace Nec
{
    template <typename T>
    class Counter {
    public:
        Counter() = default;
        explicit Counter(T val): m_cnt{ val } {}

        T get() const;
        Counter& set(T val);

        bool operator==(const Counter&);

        template <typename X>
        friend std::ostream& operator<<(std::ostream& os, const Counter<X>& c);
    private:
        T m_cnt{};
    };

#include "counter.hpp"
}

#endif // COUNTER_H