#include <iostream>

class Vector{ 
public: 
    int& front();
    const int& front() const;
};

int main(int argc, char const *argv[])
{
    using namespace std;
    
    const Vector vec;
    
    auto x = vec.front();   // legal
    vec.front() = 56;       // illegal: cunku front() const ref donuyor.
    
    return 0;
}
