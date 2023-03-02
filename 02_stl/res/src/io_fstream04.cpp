#include <iostream>
#include <fstream>
#include <string>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    ifstream ifs{ "fstream01.txt" };
    if (!ifs) {
        cerr << "dosya acilamadi\n";
        return 1;
    }

    char c;
    while (ifs.get(c))
    {
        cout << c;
    }
    
    ifs.clear();    // DIKKAT: Ustteki dongunden cikarken stream failed state'e girdi!
    
    ifs.close();

    ifs.open("fstream02.txt");
}
