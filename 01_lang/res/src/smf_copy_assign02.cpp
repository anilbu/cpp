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

    String(const String &other) : mlen{other.mlen},
                                  mp{static_cast<char *>(std::malloc(mlen + 1))}
    {
        if (!mp)
        {
            throw std::runtime_error{"cannot allocate memory"};
        }
        std::strcpy(mp, other.mp);
    }

    // Defaulted operator= -> shallow copy
    // String& operator=(const String& other) {
    //     mlen = other.mlen;
    //     mp = other.mp;
    //     return *this;
    // }

    String &operator=(const String &other)
    {
        // Not: Bu implementasyon strong exception guarantee saglamamaktadir.
        
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
        std::cout << "[" << mp << "]\n";
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
    String str{"Bugun gunlerden pazar ve biz C++ dilini ogreniyoruz!"};
    str.print();

    if (true)
    {
        String s{"C++ 23 standartlari artik yavas yavas kesinlesiyor."};
        s.print();

        s = str; // derleyicinin urettigi copy assignment, shallow copy yapti.
                 // s dtor calistirdiginda:
                 //  1. str'nin shallow copy ile alinmis kaynagi silinir.
                 //  2. s'in kendi orjinal kaynagi artik silinemeyecek.
        s.print();
    }

    str.print();
    
    // (1)
    int x = 10;
    x = x;  // self assignment
    
    int* p = &x;
    int& r = x;
    *p = x; // self assignment var!
    
    
    str = str;
    str.print();
}
