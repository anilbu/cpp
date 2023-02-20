#include <iostream>
#include <cstdlib>
#include <cstring>

class String
{
public:
    String() = default;

    String(const char *p) : mlen{std::strlen(p)},
                            mp{static_cast<char *>(std::malloc(mlen + 1))}
    {
        if (!mp)
        {
            throw std::runtime_error{"cannot allocate memory"};
        }
        std::strcpy(mp, p);
    }
    
    // Defaulted copy ctor -> shallow copy
    // String(const String &copy) : mlen{copy.mlen},
    //                              mp{copy.mp}
    // {
    // }

    ~String()
    {
        if (mp)
        {
            std::free(mp);
        }
    }

    void print() const
    {
        std::cout << "[" << mp << "]\n";
    }

    std::size_t length() const
    {
        return mlen;
    }

private:
    std::size_t mlen{};
    char *mp{};
};


void func(String s)
{
    std::cout << "func cagrildi\n";
    s.print();
}

int main(int argc, char const *argv[])
{
    String str{"Bugun gunlerden pazar ve havada UB kokusu var..."};
    str.print();
    std::cout << "str.length() = " << str.length() << '\n';

    func(str);

    str.print();
    std::cout << "str.length() = " << str.length() << '\n';
}
