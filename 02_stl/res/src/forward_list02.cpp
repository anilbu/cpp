#include <iostream>
#include <iterator>
#include <string>
#include <forward_list>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        forward_list<string> x {"d", "e", "f"};
        print(x);

        // listenin basina ekle
        x.insert_after(x.before_begin(), "c");  // dikkat: before_begin
        print(x);

        // listenin basina 3 tane ekle
        x.insert_after(x.before_begin(), 2, "a");
        print(x);
    }
}
