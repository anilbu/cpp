#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <list>
#include <utility>
#include "nutility.h"


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        vector<string> svec;
        
        rfill(svec, 20, rname);
        print(svec);
        
        const auto f_pred = [](const string& s) {
            return s.front() == 'a';
        };
        auto iter = partition(svec.begin(), svec.end(), f_pred);

        print(svec.begin(), iter); // svec: ali ahmet ayse necati mehmet
        print(iter, svec.end()); // svec: ali ahmet ayse
        cout << "Kosulu saglayan " << std::distance(svec.begin(), iter) << " oge var\n";
        cout << "Kosulu saglamayan ilk oge = " << *iter << '\n';
        
        auto iter_part_point = partition_point(svec.begin(), svec.end(), f_pred);
        std::cout << "*iter_part_point = " << *iter_part_point << '\n';
    }
    {
        vector<int> ivec;
        rfill(ivec, 20, Irand{ 0, 100 });

        vector<int> primes;
        list<int> non_primes;

        // pair<vector<int>::iterator, list<int>::iterator> ip1 =
        // auto ip1 = partition_copy(ivec.begin(), ivec.end(), primes.begin(), non_primes.begin(), &isprime);
        
        
        pair<back_insert_iterator<vector<int>>, back_insert_iterator<list<int>>> ip2 =
        // auto iter_pair = 
        partition_copy(ivec.begin(), ivec.end(), back_inserter(primes), back_inserter(non_primes), &isprime);
        

    }
}
