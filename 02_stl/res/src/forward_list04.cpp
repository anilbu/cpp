#include <iostream>
#include <iterator>
#include <algorithm>
#include <string>
#include <forward_list>
#include "nutility.h"

template <typename FwIter>
class before_iterator
{
public:
    using iterator_category = std::forward_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = typename FwIter::value_type;
    using pointer           = value_type*;
    using reference         = value_type&;
    
    before_iterator() : 
        m_iter{},
        m_prev{}
    {
    }
    
    before_iterator(FwIter _iter) :
        m_iter { _iter != FwIter{} ? next(_iter) : _iter}, 
        m_prev{ _iter }
    {
    };
    
    reference operator*() const 
    {
        return *m_iter;
    }
    
    pointer operator->() 
    {
        return &*m_iter;
    }
    
    FwIter& operator++() 
    {
        m_prev = m_iter;
        return ++m_iter;
    }
    
    FwIter operator++(int) 
    {
        m_prev = m_iter++;
        return m_prev;
    }
    
    // TODO template olmadigi durumu arastir
    template <typename Iter>
    bool operator==(const Iter& it) const
    {
        return m_iter == it;
    }
    
    FwIter base() const
    {
        return m_prev;
    }
private:
    FwIter m_iter;
    FwIter m_prev;
};

template <typename FwIter>
before_iterator<FwIter> make_before_iterator(FwIter iter){
    return before_iterator<FwIter>(iter);
}

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        forward_list<string> x {"x", "a", "b", "y", "c", "d", "e", "z"};
        print(x);
        
        auto before_iter = make_before_iterator(x.before_begin());

    
        if(auto iter = find(before_iterator(x.before_begin()), {}, "x"); iter != x.end())
        {
            std::cout << "*iter = " << *iter << '\n';
            x.erase_after(iter.base());
            print(x);
        }
        
        if(auto iter = find(before_iterator(x.before_begin()), {}, "y"); iter != x.end())
        {
            std::cout << "*iter = " << *iter << '\n';
            x.erase_after(iter.base());
            print(x);
        }
        
        if(auto iter = find(before_iterator(x.before_begin()), {}, "z"); iter != x.end())
        {
            std::cout << "*iter = " << *iter << '\n';
            x.erase_after(iter.base());
            print(x);
        }
    }
}
