#include <iostream>
#include <cstdlib>

struct Myclass {
public:
    Myclass() {
        std::cout << "Myclass()  this = " << this << "\n";
    }

    ~Myclass() {
        std::cout << "~Myclass() this = " << this << "\n";
    }


    void* operator new(size_t sz)
    {
        std::cout << "Myclass::operator new(size_t sz)  sz = " << sz << '\n';
        auto vp = std::malloc(sz);
        if (!vp)
            throw std::bad_alloc{};

        std::cout << "address of the allocated block: " << vp << '\n';
        return vp;
    }

    void operator delete(void* vp)
    {
        std::cout << "Myclass::operator delete(void* vp) vp = " << vp << '\n';
        std::free(vp);
    }

private:
    unsigned char buffer[1024]{};
};

int main(int argc, char const *argv[])
{
    using namespace std;

    std::cout << "sizeof(Myclass) = " << sizeof(Myclass) << '\n';
    // auto m = new Myclass;
    // delete m;

    auto m2 = new ::Myclass;        // global new ile cagrilmasi
    ::delete m2;
}