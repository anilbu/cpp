#include <iostream>
#include <memory>

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
    // auto p = new ResourceUser{ 4 };
    auto up = std::make_unique<ResourceUser>(4);
    throw 1;
    // delete p;
}

void f3() 
{
    // auto p = new ResourceUser{ 3 };
    auto up = std::make_unique<ResourceUser>(3);
    f4();
    // delete p;
}

void f2() 
{
    // auto p = new ResourceUser{ 2 };
    auto up = std::make_unique<ResourceUser>(2);
    f3();
    // delete p;
}

void f1() 
{
    // auto p = new ResourceUser{ 1 };
    auto up = std::make_unique<ResourceUser>(1);
    f2();
    // delete p;
}

int main(int argc, char const *argv[])
{
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
