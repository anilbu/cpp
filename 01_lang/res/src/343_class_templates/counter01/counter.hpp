namespace Nec {
    template <typename T>
    T Counter<T>::get() const
    {
        return m_cnt;
    }

    template <typename T>
    Counter<T>& Counter<T>::set(T val)
    {
        m_cnt = val;
        return *this;
    }

    template <typename T>
    bool Counter<T>::operator==(const Counter& other)
    {
        return m_cnt == other.m_cnt;
    }

    template <typename T>
    std::ostream& operator<<(std::ostream& os, const Counter<T>& c)
    {
        return os << c.m_cnt;
    }

}