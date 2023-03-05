#include <list>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <iterator>
#include <iostream>
#include "nutility.h"

/* 
    Bir listedeki ogeler kopyalanmadan RandIter ile kullanimi gereken senaryolarda kullanilabilir.
*/

int main()
{
    using namespace std;
    
    // FwIter
    list<string> slist{ "hasan", "demir", "nur", "kaya", "berk" };
    
    // RandIter
    vector<reference_wrapper<string>> refvec{ slist.begin(), slist.end() };
    
    // shuffle bir RandIter istiyor
    shuffle(refvec.begin(), refvec.end(), mt19937{ random_device{}() });
    
    
    copy(refvec.begin(), refvec.end(), ostream_iterator<string>{cout, " "});
    cout << '\n';

    for (auto& s : refvec) {
        s.get() += "can";
    }

    copy(slist.begin(), slist.end(), ostream_iterator<string>{cout, " "});
    cout << '\n';
}