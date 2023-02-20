#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;

    int x = 5;
    int y = 9;
    int a = x +++ y;
    
    cout << "x = " << x << endl;  // 6
    cout << "y = " << y << endl;  // 9
    cout << "a = " << a << endl;  // 14
}
