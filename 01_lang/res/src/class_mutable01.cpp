#include <mutex> 

class Date {
public:
    void print() const {
        mlock.lock();
        m_debug_cnt;
    }
    
private:
    int md, mm, my;
    mutable std::mutex mlock;
    mutable int m_debug_cnt; 
};
