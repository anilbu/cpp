#include <iostream>
#include <functional>
#include <vector>

void func() 
{
    std::cout << "func()\n";
}

struct Functor {
    void operator()() {
        std::cout << "Functor::operator()\n";
    }
};

int main(int argc, char const *argv[])
{
    using namespace std;
    int a = 0;
    
    vector<function<void()>> fvec;

    fvec.emplace_back(Functor{});
    fvec.emplace_back(func);
    fvec.emplace_back(&func);
    fvec.emplace_back([]{ std::cout << "stateless lambda\n"; });
    fvec.emplace_back([a]{ std::cout << "stateful lambda\n"; });
    fvec.emplace_back(+[]{ std::cout << "positive lambda\n"; });

    for (auto& f : fvec)
        f();
}