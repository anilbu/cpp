#include <iostream>
#include <cassert>


enum Nec { on, off, hold};

int main(int argc, char const *argv[])
{
    assert(sizeof(Nec) == sizeof(int));
    
}
