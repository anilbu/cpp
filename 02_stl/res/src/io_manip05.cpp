#include <iostream>

std::ostream& starline(std::ostream& os)
{
    return os << "***************\n";
}


class ns {
public:
    ns(int n) : _val {n} {}
    
    friend std::ostream& operator<<(std::ostream& os, const ns& x)
    {
        return os << std::string(x._val, ' ');
    }
private:
    int _val;
};


int main(int argc, char const *argv[])
{
    using namespace std;
    cout << 23 << starline << 12 << starline << 89 << starline;
    cout << 23 << ns(5) << 12 << ns(15) << 89 << ns(25);
}
