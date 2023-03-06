#include <iostream>

void* operator new(std::size_t sz)
{
    std::cout << "operator new called for the size of " << sz << '\n';

    if (sz == 0)
        ++sz;

    void* ptr = std::malloc(sz);
    if (!ptr)
        throw std::bad_alloc{};

    std::cout << "the address of the allocated block is " << ptr << '\n';
    return ptr;
}

void operator delete(void* ptr) noexcept
{
    std::cout << "operator delete called for address " << ptr << '\n';
    std::free(ptr);
}

class Myclass {
public:
    Myclass() {
        std::cout << "Myclass() this = " << this << '\n';
    }

    ~Myclass() {
        std::cout << "~Myclass() this = " << this << '\n';
    }
private:
    unsigned char buffer[1024]{};
};

int main(int argc, char const *argv[])
{
    auto p = new Myclass;
    delete p;
}