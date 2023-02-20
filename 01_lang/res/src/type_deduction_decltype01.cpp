#include <iostream>

struct Data{
    int a, b, c;
};

int main(int argc, char const *argv[])
{
    Data mdata;
    Data* p = &mdata;

    decltype(mdata.a);
    decltype(p->b);
    
    decltype(10);
    
}
