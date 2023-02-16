#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int zbrojiKvadrate (int *polje, int n){
	int i;
	if (n>=0){
	i = zbrojiKvadrate (polje, n-1);
	if ((float)sqrt(i) == (int)sqrt(i)){
		return *(polje+n) + i;
	}	else	{
		return i;
	}
	
	}	else	{
		return i;
	}
}

int main(void){
	int n, i;
	int *polje;
	scanf("%d", &n);
	polje = (int*) malloc(sizeof(int)*n);
	for(i=0; i<n; i++){
		scanf("%d", polje + i);
	}	
	printf("\n%d", zbrojiKvadrate(polje, n));
	
	return 0;
}
