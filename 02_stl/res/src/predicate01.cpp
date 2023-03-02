#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include "nutility.h"

template <std::size_t n>
bool is_len_same(const std::string &s)
{
    return s.length() == n;
}

class LenPred
{
public:
    explicit LenPred(std::size_t len): m_len{ len } {};

    bool operator()(const std::string &s) const
    {
        return s.length() == m_len;
    }

private:
    std::size_t m_len;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    
    vector<string> svec;
    rfill(svec, 100, rtown);
    int len = 15;
    {
        auto iter = std::find_if(svec.begin(), svec.end(), is_len_same<15>);
    }
    {
        auto iter = std::find_if(svec.begin(), svec.end(), LenPred{ len });
    }
    {
        auto iter = std::find_if(svec.begin(), svec.end(),
            [len](const std::string &s) { return s.length() == len; }
        );
    }
}
