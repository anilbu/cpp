#include <iostream>
#include <exception>
#include <stdexcept>
#include <algorithm>


class Myclass {
public:
    Myclass(): m_p{ new int[100] }
    {
        if (true)
            throw std::runtime_error("dtor will not be called when ctor failed!");
    }

    ~Myclass() {
        std::cout << "~Myclass()";
        delete[] m_p;
    }

private:
    int* m_p;
};


int main(int argc, char const *argv[])
{
    try {
        Myclass myclass;
    }
    catch (const std::exception& ex) {
        std::cout << "Exception caught: " << ex.what() << '\n';
    }
}
