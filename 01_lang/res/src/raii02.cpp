#define _CRT_SECURE_NO_WARNINGS

#include <iostream>
#include <string>
#include <cstdio>
#include <stdexcept>

class Logger
{
public:
    Logger(const char *pfname) : m_f(std::fopen(pfname, "w"))
    {
        if (!m_f)
            throw std::runtime_error{"cannot create file!"};
    }

    void log(const char *p)
    {
        std::fprintf(m_f, "%s\n", p);
    }

    ~Logger()
    {
        if (m_f)
        {
            std::fclose(m_f);
        }
    }

private:
    FILE *m_f;  // handle
};

int main(int argc, char const *argv[])
{
    Logger mlogger{"logfile.txt"};
    mlogger.log("Bu zaman noktasinda bir log girisi olustu");

    Logger* p = new Logger{ "necati.txt" };
    p->log("hata hata hata");
    
    /*
        p delete edilmez ise:
            1. resource leak olusuyor.
            2. ayrica sizeof(Logger) kadar bellek alani free edilmez.
            
        Ancak resource leak'e neden olan dtor'un cagrilmamasidir.
    */
    
    delete p;
}
