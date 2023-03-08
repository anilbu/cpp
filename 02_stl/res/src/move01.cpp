#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include "nutility.h"

class Myclass {
public:
    Myclass(): tag{ "default" }
    {
        std::cout << "Myclass()\n";
    }

    Myclass(std::string _tag):tag{ std::move(_tag) }
    {
        std::cout << "Myclass() tag = " << tag << "\n";
    }

    friend std::ostream& operator<<(std::ostream& os, const Myclass& m)
    {
        return os << m.tag;
    }

    ~Myclass()
    {
        std::cout << "~Myclass() tag = " << tag << "\n";
    }
private:
    std::string tag;
};

std::unique_ptr<Myclass> create_object()
{
    static size_t n = 0;
    return std::make_unique<Myclass>("obj" + std::to_string(n++));
}

int main(int argc, char const *argv[])
{
    using namespace std;
    using MyclassPtr = std::unique_ptr<Myclass>;

    vector<MyclassPtr> pvec(3);
    vector<MyclassPtr> dest_pvec(3);
    
    for (int i = 0; i < 3; ++i)
        pvec.push_back(create_object());

    std::cout << "pvec.size() = " << pvec.size() << '\n';
    for (auto &&uptr : pvec)
        std::cout << (uptr ? "dolu" : "bos") << ' ';
    std::cout << '\n';
    
    move(pvec.begin(), pvec.end(), dest_pvec.begin());

    std::cout << "pvec.size() = " << pvec.size() << '\n';
    for (auto &&uptr : pvec)
        std::cout << (uptr ? "dolu" : "bos") << ' ';

    std::cout << '\n';
}