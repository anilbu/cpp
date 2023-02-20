#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;

    int a[5]{ 1, 2, 3, 4, 5 };    // int[5]
    int(&ra)[5] = a;             // int[5] turunden bir diziye reference
    int(*pa)[5] = &a;            // int[5] turunden bir diziye pointer

    auto& ra = a;                 // int[5] turunden bir diziye reference

    typedef int ar_type[5];       // ar_type is int[5] type 
    using ar_type = int[5];       // ar_type is int[5] type (only C++)
    ar_type& ar = a;

    int b[5][10][20] = { 0 };
    int (&r20)[20] = b[1][2];     // r20 is reference to int[20]
}
