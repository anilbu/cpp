#include <iostream>
#include <exception>
#include <cassert>

#define func_start() (std::cout << __func__ << " starts\n")
#define func_end() (std::cout << __func__ << " ends\n")

void f2(){
    func_start();
    throw 1;
    func_end();
}

void f1(){
    func_start();
    f2();
    func_end();
}

void custom_abort()
{
    func_start();
    std::cout << "Program sonlandirilmadan once bazi islemler yapiliyor...\n";
    std::exit(EXIT_FAILURE);
    func_end();
}

int main(int argc, char const *argv[])
{
    func_start();
    auto prev_handler = std::set_terminate(custom_abort);
    
    f1();
    
    func_end();
}
