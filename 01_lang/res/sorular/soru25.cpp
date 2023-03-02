#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

/*
    Asagidaki kod orneginde Runtime error (RTE) var midir?
*/

int main(int argc, char const *argv[])
{
    using namespace std;
    vector<int> ivec_src {1, 3, 5, 7, 9};
    vector<int> ivec_dst;

    copy(ivec_src.begin(), ivec_src.end(), ivec_dst.begin());
}




















































/*
  copy algoritmasinda ivec_dest'in olusturulmamis ogesine deref yapilacagi icin UB olusur.
  runtime error olusturur.
*/