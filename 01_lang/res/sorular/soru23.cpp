#include <stdio.h>

/*
    Kodda bir hata var mi? Yoksa, ciktisi nedir?
*/


int main(int argc, char const *argv[])
{
    int x = 10, y = 20;
    int z;

    z = x, y;
    printf("z = %d\n", z);

    z = (x, y);
    printf("z = %d\n", z);
}
