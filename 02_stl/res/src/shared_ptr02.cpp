#include <iostream>
#include <memory>
#include <string>

void* operator new(std::size_t sz)
{
    std::cout << "operator new(size_t) sz = " << sz << ' ';
    if(sz == 0) ++sz;
    
    if(void* ptr = std::malloc(sz)) {
        std::cout << "@" << ptr << '\n';
        return ptr;
    }
        
    throw std::bad_alloc{};
}

void operator delete(void* ptr) noexcept {
    std::cout << "operator delete(void*) ptr = " << ptr << '\n';
    std::free(ptr);
}

class Myclass {
public:
private:
    unsigned char buf[512]{};
};

int main(int argc, char const *argv[])
{
    using namespace std;

    {
        // Myclass icin ayri control blogu icin ayri iki kere allocation yapilir.
        shared_ptr<Myclass> sptr{ new Myclass };
    }
    cout << "---------------\n";
    {
        // tek allocation ile hem Myclas icin hemde control blogu icin
        auto sp = make_shared<Myclass>();   
    }
    cout << "---------------\n";

}

