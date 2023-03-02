#include <iostream>
#include <random>
#include <sstream>

int main(int argc, char const *argv[])
{
    using namespace std;

    mt19937 eng;
    eng.discard(100);
    stringstream ss;
    ss << eng;
    
    //...
    
    mt19937 eng2;
    ss >> eng2;
    
    cout << (eng == eng2 ? "same" : "different") << " state\n";
    
    for (size_t i = 0; i < 5; i++)
    {
        cout << eng() << " " << eng2() << '\n';
    }
    
}
