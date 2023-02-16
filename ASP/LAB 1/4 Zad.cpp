#include <stdio.h>
#include <stdlib.h>

double exp(double x, int n, int *fakt, double *xpot){
	if (n == 0){
		return 1;
	}	else {
		return *(xpot)/(*(fakt)) + exp(x, n-1, fakt, xpot);
	}
}

int fakt1(int n){
	if (n == 1 || n == 0)
    {
				return 1;
    }else
    {
        return n*fakt1(n-1);
    }
}

double xpot1(int x, int n){
	if(n == 0){
		return 1;
	}  else  {
		return x*xpot1(x, n-1);
	}
}

int main(void){
	int n, x, i, faktp1, *poljef;
	double *polje, xpotp1, *poljex;
	scanf("%d %d", &n, &x);
	polje = (double*) malloc(sizeof(double)*n);
	poljef = (int*) malloc(sizeof(int)*n);
	poljex = (double*) malloc(sizeof(double)*n);
	for(i=0; i<n; i++){
		faktp1 = fakt1(i);
		xpotp1 = xpot1(x, i);
		poljef = &faktp1;
		poljex = &xpotp1;
		poljef ++;
		poljex ++;
		*(polje+i) = exp(x, i, poljef, poljex);
		printf("\n%lf", *(polje+i));
	}
	return 0;
}
