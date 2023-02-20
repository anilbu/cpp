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

    String(const String &other) : mlen{other.mlen},
                                  mp{static_cast<char *>(std::malloc(mlen + 1))}
    {
        if (!mp)
        {
            throw std::runtime_error{"cannot allocate memory"};
        }
        std::strcpy(mp, other.mp);
    }
    
    String &operator=(const String &other)
    {
        // self assignment guard
        if(this == &other)
            return *this;
        
        // release original resource
        if(mp){
            std::free(mp);
        }
    
        // make a deep copy
        mlen = other.mlen;
        mp = static_cast<char *>(std::malloc(mlen + 1));
        if (!mp)
        {
            throw std::runtime_error{"cannot allocate memory"};
        }
        std::strcpy(mp, other.mp);

        return *this;
    }

    String(String&& other) : mlen{other.mlen}, mp{other.mp}
    {
        // nesneyi valid bir state'de birakilmasi gerekmektedir.
        other.mlen = 0;
        other.mp = nullptr;
    }

    ~String()
    {
        if (mp)
        {
            std::free(mp);
        }
    }

    //...

    void print() const
    {
        std::cout << "[" << (mp ? mp : "") << "]\n";
    }

    std::size_t length() const
    {
        return mlen;
    }

    //...

private:
    std::size_t mlen{};
    char *mp{};
};

int main(int argc, char const *argv[])
{
    String s1{ String{"test"} };
    s1.print();
    
    std::cout << "----------------\n";
    
    String s2{"Bugun gunlerden pazar ve biz C++ dilini ogreniyoruz!"};
    String s3{std::move(s2)};
    s2.print();
    s3.print();
    
    std::cout << std::endl;
}
