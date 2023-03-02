#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    vector<string> x(100'000);
    vector<string> y(100'000);
    
    // Tertermiz bir bicimde katledilmis C++ kodu
    // auto temp = x;
    // x = y;
    // y = temp;
    
    x.swap(y);
    swap(x, y);
}
