#include <iostream>
#include <algorithm>
#include <string>
#include <deque>
#include "nutility.h"

int main(int argc, char const *argv[])
{
    using namespace std;
    
    deque<int> ideq;
    Irand rand{0, 100};
    for (int i = 0; i < 20; i++)
    {
        auto val = rand();
        std::cout << "val = " << val << '\n';
        if(val % 2 == 0)
            ideq.push_front(val);
        else
            ideq.push_back(val);
            
        print(ideq);
        (void) getchar();
    }
}
