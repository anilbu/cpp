#include <iostream>

class Myclass
{
public:
    Myclass()
    {
        ++ms_live_cnt;
        ++ms_lived_cnt;
    }

    Myclass(int)
    {
        ++ms_live_cnt;
        ++ms_lived_cnt;
    }

    // kopyalamaya karsi kapatildi, move members not-declared
    Myclass(const Myclass &) = delete;
    Myclass &operator=(const Myclass &) = delete;

    ~Myclass()
    {
        --ms_live_cnt;
    }
    
    static int get_live_cnt()
    {
        return ms_live_cnt;
    }

    static int get_lived_cnt()
    {
        return ms_lived_cnt;
    }

private:
    static inline int ms_live_cnt{};
    static inline int ms_lived_cnt{};
};

int main(int argc, char const *argv[])
{
    Myclass m1, m2, m3;

    auto p1 = new Myclass{3};
    auto p2 = new Myclass{5};
    
    std::cout << Myclass::get_live_cnt() << '\n';
    
    delete p1;
    delete p2;
    
    std::cout << Myclass::get_live_cnt() << '\n';
    std::cout << Myclass::get_lived_cnt() << '\n';
}
