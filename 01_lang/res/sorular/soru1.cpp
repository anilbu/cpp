#include <iostream>

#define asize(a)    ((sizeof(a)/sizeof(*a)))

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int a[5] = {0, 1, 2, 3, 4};
    
    for (int i = -2; i < asize(a) - 2; ++i)
    {
        cout << a[i+2] << ' ';
    }
}
