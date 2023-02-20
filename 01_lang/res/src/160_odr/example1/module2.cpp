#include <iostream>

static int f(int x, int y)
{
    return x * y + 5;
}

void module2_print_f_addr()
{
    auto n = f(1, 2);
    std::cout << "&f = " << &f << '\n';
}
