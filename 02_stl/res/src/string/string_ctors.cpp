#include <iostream>
#include <string>


int main(int argc, char const *argv[])
{
    using namespace std;

    {
        // default ctor
        string s;

        std::cout << "s.size() = " << s.size() << '\n';        // s.size() = 0
        std::cout << "s.length() = " << s.length() << '\n';    // s.length() = 0
        std::cout << "s.empty() = " << s.empty() << '\n';      // s.empty() = 1
    } 
    std::cout << "------------------------\n";
    {
        // copy ctor
        string s1(10, 'A');
        string s2(s1);

        std::cout << "s1 = " << s1 << '\n';                   // s1 = AAAAAAAAAA
        std::cout << "s2 = " << s2 << '\n';                   // s2 = AAAAAAAAAA
    }
    std::cout << "------------------------\n";
    {
        // move ctor
        string s1(10, 'A');
        string s2 = std::move(s1);

        std::cout << "s1 = " << s1 << '\n';                   // s1 = 
        std::cout << "s2 = " << s2 << '\n';                   // s2 = AAAAAAAAAA
    }
    std::cout << "------------------------\n";
    {
        // cstring ctor
        char s[] = "mehmet akif";
        string str{ s + 7 };
        std::cout << "str = " << str << '\n';                      // str = akif
    }
    std::cout << "------------------------\n";
    {
        // data ctor
        char str[] = "nedim yanardoner";
        string s1(str, 5);
        std::cout << "s1 = " << s1 << '\n';                        // s1 = nedim

        string s2(str + 3, 2);                                        // s2 = im
        std::cout << "s2 = " << s2 << '\n';

        string s3(str, 20);
        std::cout << "s3.length() = " << s3.length() << '\n';// s3.length() = 20
    }
    std::cout << "------------------------\n";
    {
        //range ctor
        char str[] = "polat ersoz";
        string s{ str, str + 5 };
        std::cout << "s = " << s << '\n';                           // s = polat
    }
    std::cout << "------------------------\n";
    {
        //initializer_list ctor
        string s1{ 'a', 'l', 'i' };
        std::cout << "s1 = " << s1 << '\n';                          // s1 = ali
        
        string s2 = { 65, 66, 67, 68 }; // = olmasi anlamsal acidan bir farki yok
        std::cout << "s2 = " << s2 << '\n';                         // s2 = ABCD
    }
    std::cout << "------------------------\n";
    {
        //fill ctor
        size_t n = 10;
        string s1(n, '*');                      
        std::cout << "s1 = " << s1 << '\n';                   // s1 = **********
    }
    std::cout << "------------------------\n";
    {
        string name{ "necatiergin" };
        string str1(name, 6);
        std::cout << "str1 = " << str1 << '\n'; // str1 = ergin

        string str2(name, 1);
        std::cout << "str2 = " << str2 << '\n'; // str2 = ecatiergin

        string str3(name, 6, 3);
        std::cout << "str3 = " << str3 << '\n'; // str3 = erg
        
        // well defined: geriye kalanlarin tumu
        string str4(name, 6, 40);
        std::cout << "str4 = " << str4 << '\n'; // str4 = ergin 

        try {
            // index out of range olursa exception
            // uzunluk out of range olursa well-defined
            string str(name, 40, 300);  // throws exception, cunku 40. index yok
        }
        catch (const std::exception& ex) {
            cout << "exception caught: " << ex.what() << '\n';
        }
    }
}