#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <iomanip>

void example1()
{
    using namespace std;
    int x;

    while (cin >> x) {   // cin.operator>>(x).operator bool()
        cout << x << " * " << x << " = " << x * x << '\n';
    }
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    ifstream ifs{ "io_state02.cpp" };
    string sline;
    
    while(getline(ifs, sline)) {
        reverse(begin(sline), end(sline));
        cout << setw(80) << sline << '\n';
    }
}
