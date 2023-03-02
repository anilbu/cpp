#include <iostream>
#include <algorithm>
#include <string>
#include <vector>



int main(int argc, char const *argv[])
{
    using namespace std;
    vector<int> ivec { 1, 3, 5, 7, 9};

    {
        for (size_t i = 0; i < ivec.size(); i++)
        {
            std::cout << ivec[i] << ' ';
        }
        std::cout << '\n';
    }
    {
        // cout << ivec[20] << '\n';   //RTE

        try
        {
            cout << ivec.at(20) << '\n';   //exception
        }
        // catch(const std::exception& e)
        // catch(const std::logic_error& e)
        catch(const std::out_of_range& e)
        {
            std::cerr << "Error = " << e.what() << '\n';
        }
        
    }
}
