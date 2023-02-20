#include <iostream>

void* operator new(std::size_t sz) {
    std::cout << "operator new called for the size of:" << sz << '\n';
    
    if(sz == 0)
        ++sz;
        
    if(void* ptr = std::malloc((sz)))
        return ptr;
        
    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept 
{
    std::cout << "operator delete called for the address of:" << ptr << '\n';
    std::free(ptr);
}

class Myclass {
public:
    Myclass() {
        std::cout << "address of this = " << this << '\n';
        throw std::runtime_error{ "hata..." };
        std::cout << "Myclass ctor\n";
    }
private:
    char buffer[1024] {};
};

void foo() {
    Myclass* p = new Myclass;
    
    delete p;
}


int main(int argc, char const *argv[])
{
    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    
    try
    {
        foo();
    }
    catch(const std::exception& e)
    {
        std::cerr << "Exception caught: " << e.what() << '\n';
    }
    
}

