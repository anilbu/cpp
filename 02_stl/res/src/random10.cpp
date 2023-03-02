#include <iostream>
#include <random>
#include <map>
#include <sstream>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    uniform_int_distribution<> dist_x{1, 31};
    mt19937 eng;

    stringstream ss;
    ss << dist_x;
    
    uniform_int_distribution<> dist_y{};
    
    ss >> dist_y;
    
    cout << boolalpha << (dist_x == dist_y) << '\n';

}
