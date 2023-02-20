#include <iostream>

int main(int argc, char const *argv[])
{
    using namespace std;
    
    int* p;
    
    if(1) {
        int x = 10;
        p = &x;
        // p is valid
    }
    
    // p is invalid
}
