#include <iostream>

std::ostream& necos(std::ostream& os)
{
    os.setf(std::ios::boolalpha | std::ios::showbase);
    os.setf(std::ios::left, std::ios::adjustfield);
    os.setf(std::ios::hex, std::ios::basefield);
    os.setf(std::ios::fixed, std::ios::floatfield);
    os.precision(12);
    return os;
}

std::ostream& nonecos(std::ostream& os)
{
    os.unsetf(std::ios::boolalpha | std::ios::showbase);
    os.unsetf(std::ios::left);
    os.unsetf(std::ios::hex);
    os.unsetf(std::ios::fixed);
    os.precision(12);
    return os;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    cout << necos << 123 << '\n';
    cout << nonecos << 123 << '\n';
}
