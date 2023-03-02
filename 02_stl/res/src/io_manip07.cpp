#include <iostream>

class ns{ 
public:
    ns(int val) : m_val{val}{}
    
    friend std::ostream& operator<<(std::ostream& os, const ns& x)
    {
        return os << std::string(x.m_val, '_');
    }
private:
    int m_val{};
};


int main(int argc, char const *argv[])
{
    using namespace std;
    
    cout << 12 << ns(5) << "ali" << ns(9) << "mehmet" << ns(23) << 1234 << '\n';
}
