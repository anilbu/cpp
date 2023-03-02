#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> svec{"ali", "ata", "deniz"};
        print(svec);
        
        svec = {"gul", "naz", "nur", "can"};    // initializer_list
        print(svec);
    }
    {
        
    }
}
