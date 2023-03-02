#include <iostream>


void example1(std::ostream& os)
{
    using namespace std;
    if (os.flags() & ios_base::boolalpha)
    {

    }
}

void example2_print(std::ostream& os)
{
    using namespace std;
    const auto flags_prev = os.flags();
    os.setf(ios_base::boolalpha | ios_base::uppercase | ios_base::showbase);

    // do operations...

    os.flags(flags_prev);
    // UYARI Tum format stateleri bu sekilde degil, sadece flagsler icin uygulanabilir.
}

void example3_print(std::ostream& os)
{
    using namespace std;
    ostream oss{ os.rdbuf() };

    oss.setf(ios_base::uppercase | ios_base::showbase | ios_base::boolalpha | ios_base::hex | ios::basefield);

    cout << true << 54807 << '\n';
    oss << true << 54807 << '\n';
}



#include <fstream>

void example4_ifs()
{
    using namespace std;
    ifstream ifs{ "input.txt" };
    cout << ifs.rdbuf();
}


void example5_flags(std::ostream& os)
{
    using namespace std;
    const auto flags_prev = os.setf(ios_base::boolalpha | ios_base::uppercase | ios_base::showbase);

    // do operations...

    os.flags(flags_prev);
}

int main(int argc, char const *argv[])
{
    using namespace std;

}
