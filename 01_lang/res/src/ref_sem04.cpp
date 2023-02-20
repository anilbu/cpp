#include <iostream>

struct Data {
    int a, b, c;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    
    Data mdata {3, 6, 8};
    Data& r = mdata;
    
    r.a = 10; 
    
    std::cout << "r.a = " << r.a << '\n';
    std::cout << "r.b = " << r.b << '\n';
    std::cout << "r.c = " << r.c << '\n';
}
