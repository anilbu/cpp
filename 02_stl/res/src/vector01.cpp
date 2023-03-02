#include <iostream>
#include <algorithm>
#include <string>
#include <vector>



int main(int argc, char const *argv[])
{
    using namespace std;

    vector<string> svec;
    svec.reserve(100'000);
    std::cout << "size = " << svec.size() << " capacity = " << svec.capacity() << '\n';
    auto cap = svec.capacity();
    for (int i = 0; i < 1000000; ++i)
    {
        svec.push_back("necati");
        if (svec.capacity() > cap) {
            std::cout << "size = " << svec.size() << " capacity = " << svec.capacity() << '\n';
            cap = svec.capacity();
        }
    }

}
