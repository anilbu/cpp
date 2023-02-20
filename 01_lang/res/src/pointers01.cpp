#include <iostream>

int* get_value(void)
{
    int x;
    std::cin >> x;
    return &x;
}

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int* p = get_value();
    
    // *p;  // runtime error, cunku invalid pointer'a sahip
}
