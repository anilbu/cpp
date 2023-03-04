#include <iostream>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include "nutility.h"
#include "date.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        hash<int> hasher;
        int keys[]{ 761234, 761235, 91, 92, 135 };
        for (const auto& key : keys)
        {
            std::cout << "hasher(" << key << ") = " << hasher(key) << '\n';
        }
    }
    {
        hash<string> hasher;
        string keys[]{ "ali", "ahmet", "necati" };
        for (const auto& key : keys)
        {
            std::cout << "hasher(" << key << ") = " << hasher(key) << '\n';
        }
    }
}
