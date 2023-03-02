#include <iostream>
#include <sstream>
#include <bitset>
#include <iomanip>

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        ostringstream oss;
        oss << hex << showbase << 100 << '\n';
        std::string result = oss.str();
        std::cout << "result = " << result << '\n';
    }
    {
        int year = 1987;
        string name{ "furkan" };
        double wage = 23.456;

        // furkan_1987_23.46
        ostringstream oss;
        oss << name << '_' << year << '_' << fixed << setprecision(2) << wage;

        cout << oss.str() << '\n';
    }
    {
        ostringstream oss;
        oss.fill('0');
        
        for (int i = 0; i < 3; ++i)
        {
            oss.str("");
            oss << "necati" << setw(2) << i << ".txt";
            auto filename = oss.str();
            std::cout << "filename = " << filename << '\n';
        }
        
    }
}
