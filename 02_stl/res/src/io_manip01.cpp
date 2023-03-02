#include <iostream>


std::ostream& Hex(std::ostream& os)
{
    os.setf(std::ios::hex, std::ios::basefield);
    return os;
}

std::ostream& Boolalpha(std::ostream& os)
{
    os.setf(std::ios::boolalpha);
    return os;
}

std::ostream& Noboolalpha(std::ostream& os)
{
    os.unsetf(std::ios::boolalpha);
    return os;
}



int main(int argc, char const *argv[])
{
    using namespace std;
    
    int ival { 0xBABA };
    cout << ival << " " << Hex << ival << '\n';
    
    
    cout << Boolalpha << true << false << '\n';
    cout << Noboolalpha << true << false << '\n';
    
}
