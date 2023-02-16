#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#define M 128

struct zapis
{
    int sifra;
};

typedef struct zapis zapis;

unsigned long int Adresa(int value)
{
    unsigned long int A = 2654435769;
    int shift = 4;

    return ((A * value) >> shift) % M;
}

void upis(zapis *hash, zapis element)
{
    int indeks;
    int i;
    unsigned long int adresa = Adresa(element.sifra);
    for (i = 0; i < M; i++)
    {
        indeks = fmod((adresa + 0 * i + 1 * i * i), M);
        if (hash[indeks].sifra == 0)
        {
            hash[indeks] = element;
            break;
        }
    }
}

int main(void)
{
    int i;
    zapis hash[M]	= {0} ;
    zapis element;

    srand((unsigned)time(NULL));

   /* for (i = 0; i < M; i++)
        hash[i].sifra = 0;	*/
    for (i = 0; i < 129; i++)
    {
        element.sifra = rand();
        upis(hash, element);
    }

    for (i = 0; i < M; i++)
    {
        printf("%d) ", i);
        printf("%d ", hash[i].sifra);
        printf("\n");
    }

    return 0;
}
