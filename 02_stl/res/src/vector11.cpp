#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> svec{"ali", "selim", "ata", "murat", "serhat", "yesim", "serhat", "gizem", "seyhan"};

        while (!svec.empty())
        {
            print(svec);
            svec.pop_back();
        }
    }
}
