#include <stdio.h>

/*
    Asagidaki iki program gecerli midir? Programlarin ciktisi nedir?
*/

// (1)
int main(void)
{
    int printf = 5;
    printf("Merhaba dunya");
}

// (2)
int main(void)
{
    printf("Merhaba dunya");
    int printf = 5;
}
























































/*
    Dilin kurallarina gore isim arama once yapilir. 
    Bu nedenle int degisken isim arama sonucu once bulunur ve context control sonucu 
    bir int deger operator() operandi olamaz.

*/