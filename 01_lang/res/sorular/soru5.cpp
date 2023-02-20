#include <iostream>



int main(int argc, char const *argv[])
{
    using namespace std;
    
    int a[5] = {1, 2, 3, 4, 5};
    
    // oyle bir pointer olsun ki a dizisini gostersin
    // yani int[5] turunden bir varligi isaret etsin
    
    int (*p)[5] = &a;
    
    cout << sizeof(p) << '\n';
    cout << sizeof(*p) << '\n';
}
