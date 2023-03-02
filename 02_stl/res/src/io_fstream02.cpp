#include <iostream>
#include <fstream>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        ifstream ifs{};
    }
    {
        ifstream ifs{ "fstream01.txt" };
    }
    {
        // fopen("fstream02.txt", "rb");
        ifstream ifs{ "fstream01.txt", ios::in | ios::binary };
    }
    {
        ifstream ifs{ "non_existed_file.txt" };
        if (!ifs) {
            cerr << "Dosya acilamadi\n";
        }
    }
}
