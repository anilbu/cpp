#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;
    {
        vector<string> svec{"ali", "ata", "deniz"};
        print(svec);
        
        svec.assign({"gul", "naz", "nur", "can"});    // initializer_list
        print(svec);
    }
    {
        vector<string> svec{"ali", "ata", "deniz"};
        print(svec);
        
        svec.assign(20, "hakan");    // fill assign
        print(svec);
    }
    {
        vector<string> svec{"ali", "ata", "deniz"};
        print(svec);
        
        list<string> slist {"murat", "firat", "serhat", "yekta"};
        
        svec.assign(slist.begin(), slist.end());    // range assign
        print(svec);
    }
}
