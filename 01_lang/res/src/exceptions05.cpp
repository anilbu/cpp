#include <iostream>
#include <exception>

void func()
{
    throw std::out_of_range{ "out of range error" };
}

void foo()
{
    try
    {
        func();
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Exception caught in foo(): " << ex.what() << '\n';
        std::cout << &ex << '\n';
        throw;
    }
}

void bar()
{
    try
    {
        func();
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception caught in bar(): " << ex.what() << '\n';
        std::cout << &ex << '\n';
        throw ex;
    }
}

int main(int argc, char const *argv[])
{
    try
    {
        foo();
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Exception caught in main() std::out_of_range&\n";
        std::cout << &ex << '\n';
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception caught in main() std::exception&\n";
        std::cout << &ex << '\n';
    }
    std::cout << "--------------------\n";
    
    try
    {
        bar();
    }
    catch(const std::out_of_range& ex) {
        std::cout << "Exception caught in main() std::out_of_range&\n";
        std::cout << &ex << '\n';
    }
    catch(const std::exception& ex)
    {
        std::cout << "Exception caught in main() std::exception&\n";
        std::cout << &ex << '\n';
    }
}
