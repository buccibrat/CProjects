#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double f(double z, int k)
{

    if (k == 0)
    {
        return z;
    }

    return (-1) * z / (k + 1) * f(z, k - 1);
}

int main(void)
{
    double z, rj;
    int k;
    z = 0.5;

    printf("< Broj k? >");
    scanf("%d", &k);

    rj = f(z, 2 * k);

    printf("%lf ", rj);

    return 0;
}
