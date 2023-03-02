#include <iostream>
#include <random>
#include <chrono>

int main(int argc, char const *argv[])
{
    using namespace std;
    using namespace std::chrono;
    
    // time_point tp = steady_clock::now();
    // duration dur = tp.time_since_epoch();
    // auto seed = dur.count();
    // mt19937 eng(static_cast<size_t>(seed));
    
    mt19937 eng(steady_clock::now().time_since_epoch().count());
}
