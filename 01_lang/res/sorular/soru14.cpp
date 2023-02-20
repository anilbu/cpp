
/*
    Soru
    
        Asagidaki cagrilardan hangileri gecerlidir?
*/


template <typename T>
void foo(T, T);

template <typename T>
void bar(T&, T&);


int main(int argc, char const *argv[])
{
    // foo("ali", "mert");
    // foo("ali", "can");
    // bar("ali", "mert");
    // bar("ali", "can");
}































































/*

    foo("ali", "mert")
        Gecerli: const char* ve const char*
            const char[4] ve const char[5] icin decay uygulanir
            
    foo("ali", "can")
        Gecerli: const char* ve const char*
            const char[4] ve const char[4] icin decay uygulanir
            
            
    bar("ali", "mert")
        Gecersiz: const char(&)[4] ve const char(&)[5]
            
            
    bar("ali", "can")
        Gecerli: const char(&)[4] ve const char(&)[4]
            
            

*/