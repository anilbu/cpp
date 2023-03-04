#include <iostream>
#include <queue>
#include <vector>
#include "nutility.h"

template <typename T>
using gprq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        priority_queue<int> ipq1;
        priority_queue<int, vector<int>, greater<int>> ipq2;
        gprq<int> ipq3;
    }
    {
        priority_queue<int> ipq;
        Irand rand{ 0, 1000 };

        for (int i = 0; i < 10; i++) {
            auto val = rand();
            ipq.push(val);
        }

        while (!ipq.empty())
        {
            cout << ipq.top() << ' ';
            ipq.pop();
        }
        cout << "\n";
    }
    {
        priority_queue<int, vector<int>, greater<int>> ipq;
        Irand rand{ 0, 1000 };

        for (int i = 0; i < 10; i++) {
            auto val = rand();
            ipq.push(val);
        }

        while (!ipq.empty())
        {
            cout << ipq.top() << ' ';
            ipq.pop();
        }
    }
    // -----------


}