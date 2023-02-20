#include <iostream>

void module1_print_f_addr();
void module2_print_f_addr();

static int f(int x, int y)
{
    return x * y + 5;
}

int main(int argc, char const *argv[])
{
    auto n = f(1, 2);
    std::cout << "&f = " << &f << '\n';
    
    module1_print_f_addr();
    module2_print_f_addr();
}
