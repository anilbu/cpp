#include <iostream>
#include <vector>
#include <random>
#include <stack>

template <typename T>
class istack
{
public:
    void push(const T &x)
    {
        mvec.push_back(x);
    }
    
    void pop()
    {
        mvec.pop_back();
    }
    
    T& top() const
    {
        return mvec.back();
    }
    
    bool empty() const
    {
        return mvec.empty();
    }
    
    void clear()
    {
        mvec.clear();
    }

    std::size_t size() const
    {
        return mvec.size();
    }

private:
    std::vector<T> mvec;
};

int main(int argc, char const *argv[])
{
    using namespace std;

    mt19937 eng{ random_device{}() };
    uniform_int_distribution dist{ 100, 500 };

    istack<int> mstack;
    for (int i = 0; i < 20; i++)
    {
        auto val = dist(eng);
        cout << val << ' ';
        mstack.push(val);
    }

    std::cout << "stack'te " << mstack.size() << " tane oge var\n";

    while (!mstack.empty())
    {
        auto x = mstack.top();
        mstack.pop();
        std::cout << x << " cikarildi, " << mstack.size() << " oge kaldi\n";
    }

    return 0;
}
