#include <iostream>


class ResourceUser
{
private:
    int m_x;
public:
    ResourceUser(int x) : m_x{ x } {
        std::cout << "kaynak edinildi. m_x = " << m_x << '\n';
    }
    ~ResourceUser() {
        std::cout << "kaynak geri verildi. m_x = " << m_x << '\n';
    }
};

void f4() 
{
    ResourceUser x{ 4 };
    throw 1;
}

void f3() 
{
    ResourceUser x{ 3 };
    f4();    
}

void f2() 
{
    ResourceUser x{ 2 };
    f3();    
}

void f1() 
{
    ResourceUser x{ 1 };
    f2();    
}

int main(int argc, char const *argv[])
{
    // f1();    // stack unwinding calismaz!
    
    try{
        f1();
    }
    catch(int) 
    {
        std::cout << "exception caught\n";
        (void)getchar();
    }
    
    std::cout << "main devam ediyor...\n";
}
