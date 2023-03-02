#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;

    auto cfill = cout.fill();
    auto width = cout.width();

    std::cout << "cfill = " << static_cast<int>(cfill) << '\n';
    std::cout << "width = " << width << '\n';

    string str{ "necati ergin" };
    int ival{ 1874 };
    cout << ival << str << '\n';

    cout.setf(ios::left, ios::adjustfield);
    cout.width(10);
    cout.fill('_');
    cout << ival << str << '\n';

}
