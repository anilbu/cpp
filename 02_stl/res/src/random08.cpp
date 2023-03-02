#include <iostream>
#include <random>


int main(int argc, char const *argv[])
{
    using namespace std;
    
    uniform_int_distribution<> dist{2, 7};  // 7 dahil
    mt19937 eng;
    
    // dist(eng);  // dist.operator()(eng);
    
    for (int i = 0; i < 10; i++)
    {
        cout << dist(eng) << '\n';
    }
    
}
