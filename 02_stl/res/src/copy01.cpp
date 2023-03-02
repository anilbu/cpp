#include <iostream>
#include <algorithm>
#include <vector>
#include <list>
#include <string>
#include "nutility.h"
#include "date.h"

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        int a[10] = { 1, 2, 3, 4, 5 };
        int b[10];

        copy(std::begin(a), std::end(a), std::begin(b));

        print(a);
        print(b);
    }
    {
        vector<string> svec;
        rfill(svec, 10, rname);
        list<string> slist(10);

        copy(svec.begin(), svec.end(), slist.begin());
        print(svec);
        print(slist);
    }
    {
        vector<const char*> svec;
        // rfill(svec, 10, rname);

        list<string> slist(10);
        // std::copy(svec.begin(), svec.end(), slist.begin());
        // print(svec);
        // print(slist);
    }
    {
        std::vector<Date> src_vec;
        rfill(src_vec, 20, Date::random);
        
        std::vector<Date> dest_vec(src_vec.size());
        
        int mon = 1;
        auto iter = copy_if(src_vec.begin(), src_vec.end(), dest_vec.begin(),
            [mon](const Date& d) { return d.month() == mon; }
        );

        const std::size_t nCopied = std::distance(dest_vec.begin(), iter);
        std::cout << "Toplam " << nCopied << " oge kopyalandi.\n";
        print(dest_vec.begin(), iter, "\n");
    }
}
