/*
#include <iostream>
#include <format>


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        char c = 120;
        auto s0 = std::format("{:6}", 42);    // value of s0 is "    42"
        auto s1 = std::format("{:6}", 'x');   // value of s1 is "x     "
        auto s2 = std::format("{:*<6}", 'x'); // value of s2 is "x*****"
        auto s3 = std::format("{:*>6}", 'x'); // value of s3 is "*****x"
        auto s4 = std::format("{:*^6}", 'x'); // value of s4 is "**x***"
        auto s5 = std::format("{:6d}", c);    // value of s5 is "   120"
        auto s6 = std::format("{:6}", true);  // value of s6 is "true  "
    }
    {
        double inf = std::numeric_limits<double>::infinity();
        double nan = std::numeric_limits<double>::quiet_NaN();
        auto s0 = std::format("{0:},{0:+},{0:-},{0: }", 1);   // value of s0 is "1,+1,1, 1"
        auto s1 = std::format("{0:},{0:+},{0:-},{0: }", -1);  // value of s1 is "-1,-1,-1,-1"
        auto s2 = std::format("{0:},{0:+},{0:-},{0: }", inf); // value of s2 is "inf,+inf,inf, inf"
        auto s3 = std::format("{0:},{0:+},{0:-},{0: }", nan); // value of s3 is "nan,+nan,nan, nan"
    }
    {
        char c = 120;
        auto s1 = std::format("{:+06d}", c);   // value of s1 is "+00120"
        auto s2 = std::format("{:#06x}", 0xa); // value of s2 is "0x000a"
        auto s3 = std::format("{:<06}", -42);  // value of s3 is "-42   "
        // (0 is ignored because of < alignment)
    }
    {

        float pi = 3.14f;
        auto s1 = std::format("{:10f}", pi);           // s1 = "  3.140000" (width = 10)
        auto s2 = std::format("{:{}f}", pi, 10);       // s2 = "  3.140000" (width = 10)
        auto s3 = std::format("{:.5f}", pi);           // s3 = "3.14000" (precision = 5)
        auto s4 = std::format("{:.{}f}", pi, 5);       // s4 = "3.14000" (precision = 5)
        auto s5 = std::format("{:10.5f}", pi);         // s5 = "   3.14000"
                                                       // (width = 10, precision = 5)
                                                       
        auto s6 = std::format("{:{}.{}f}", pi, 10, 5); // s6 = "   3.14000"
                                                       // (width = 10, precision = 5)

        auto b1 = std::format("{:{}f}", pi, 10.0);     // throws: width is not of integral type 
        auto b2 = std::format("{:{}f}", pi, -10);      // throws: width is negative
        auto b3 = std::format("{:.{}f}", pi, 5.0);     // throws: precision is not of integral type
    }
}
*/