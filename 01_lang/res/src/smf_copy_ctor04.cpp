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
    
    // User-defined copy ctor: Deep copy uygulandi
    String(const String &other) : mlen{other.mlen},
                                 mp{static_cast<char *>(std::malloc(mlen + 1))}
    {
        if (!mp)
        {
            throw std::runtime_error{"cannot allocate memory"};
        }
        std::strcpy(mp, other.mp);
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

class Person{ 

private:
    String mname;   // Bu durumda Person sinifinin copy ctor'unu yazmamiz gerekir miydi? 
                    // Hayir: Person sinifinin default ctor'u mname member'ini kopyalarken 
                    //        zaten copy ctor cagrilacakti.
};

void func(String s)
{
    std::cout << "func cagrildi\n";
    s.print();
}

int main(int argc, char const *argv[])
{
    String str{"Bugun gunlerden sadece pazar."};
    str.print();
    std::cout << "str.length() = " << str.length() << '\n';

    func(str);

    str.print();
    std::cout << "str.length() = " << str.length() << '\n';
}
