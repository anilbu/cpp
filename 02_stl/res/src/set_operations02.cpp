#include <iostream>
#include <algorithm>
#include <vector>
#include "nutility.h"

using namespace std;

int main(int argc, char const *argv[])
{
    vector<int> odd_nums {1, 3, 5, 7, 9};
    sort(odd_nums.begin(), odd_nums.end());
    print(odd_nums);

    vector<int> even_nums { 0, 2, 4, 6, 8 };
    sort(even_nums.begin(), even_nums.end());
    print(even_nums);

    vector<int> dest_vec;
    
    merge(odd_nums.begin(), odd_nums.end(), 
          even_nums.begin(), even_nums.end(), 
          back_inserter(dest_vec));
          
    print(dest_vec);
}
