#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <iterator>

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<int> ivec(100);
        list<int> ilst(100);

        auto ivec_first = ivec.begin();
        auto ivec_last = ivec.end();
        cout << std::distance(ivec.begin(), ivec.end()) << '\n';    // ivec_last - ivec_first

        auto ilst_first = ilst.begin();
        auto ilst_last = ilst.end();

        /*
        int n = 0;
        for (auto temp = ilst_first; temp != ilst_last; ++n, ++temp]);
        */
        cout << std::distance(ilst.begin(), ilst.end()) << '\n';
    }
    {
        vector<int> ivec {1, 3, 5, 7, 9};

        auto iter = std::find(ivec.begin(), ivec.end(), 3);

        int n_beg = std::distance(ivec.begin(), iter);
        std::cout << "n_beg = " << n_beg << '\n';
        std::cout << "*iter = " << *iter << '\n';

        int n_last = std::distance(iter, ivec.end());
        std::cout << "n_last = " << n_last << '\n';
        std::cout << "*iter = " << *iter << '\n';
    }

}
