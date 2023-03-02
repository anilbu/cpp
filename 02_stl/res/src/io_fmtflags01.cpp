#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;

    cout << (10 < 5) << '\n';

    cout.setf(ios::boolalpha);

    cout << (10 < 5) << '\n';
    cout << (10 < 5) << '\n';

    cout.unsetf(ios::boolalpha);
    cout << (10 < 5) << '\n';
    cout << (10 < 5) << '\n';
}
