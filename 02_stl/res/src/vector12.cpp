#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

void print_array(const int* p, size_t sz)
{
    while (size--)
        printf("%d ", *p++);
    printf("\n--------------------\n");
}

int main(int argc, char const *argv[])
{
    using namespace std;
    vector<int> ivec{3, 4, 5, 6, 7, 8, 9};
    print_array(ivec.data(), ivec.size());
    
    // alternatifler olarak:
    print_array(&ivec[0], ivec.size());
    print_array(&*ivec.begin(), ivec.size());
}
