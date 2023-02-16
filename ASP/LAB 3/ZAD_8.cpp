#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <math.h>
#define M 128

struct zapis
{
    int broj;
    struct zapis *sljed;
};

typedef struct zapis zapis;

unsigned long int adresa(int value)
{
    unsigned long int A = 2654435769;
    int shift = 4;

    return ((A * value) >> shift) % M;
}

int upis(zapis **hash, int k)
{
    zapis *novi;
    int adr;
    novi = (zapis *)malloc(sizeof(zapis));
    if (novi == NULL)
        return 0;
    adr = adresa(k);
    novi->sljed = hash[adr];
    novi->broj = k;
    hash[adr] = novi;
    return 1;
}

int main(void)
{
    int i;
    zapis *hash[M] = {0}
		;
    zapis *clan;

    srand((unsigned)time(NULL));

  
    for (i = 0; i < 129; i++)
    {
        upis(hash, rand());
    }

    for (i = 0; i < M; i++)
    {
        printf("%d) ", i);
        clan = hash[i];
        while (clan)
        {
            printf("%d ", clan->broj);
            clan = clan->sljed;
        }
        printf("\n");
        printf("\n");
    }

    getchar();
    return 0;
}
