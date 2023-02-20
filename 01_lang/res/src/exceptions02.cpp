#include <iostream>
#include <vector>


int main(int argc, char const *argv[])
{
    return 0;   // dikkat: linux'da farkli calisabiliyor
    
    using namespace std;
    
    vector<char*> cvec;

    try
    {
        for (int i = 0; i < 300'000'000; i++)
        {
            cvec.push_back(new char[1024 * 1024]);
        }
    }
    catch(const std::exception& e)
    {
        std::cerr << "exception caught: " << e.what() << '\n';
    }
    
    std::cout << "cvec.size() = " << cvec.size() << '\n';
}
