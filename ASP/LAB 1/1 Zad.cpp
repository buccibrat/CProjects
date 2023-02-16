#include <stdio.h>
#include <stdlib.h>
void ispis(float *polje, int n){
	if (n <= 0){
		printf("\nNema vise clanova polja");
	}	else	{
		ispis(polje, n-1);
		if(*(polje + n) < 0){
			printf("\n%f", *(polje + n));			
		}
	}
}

int main(void){
	int n, i;
	float *polje;
	scanf("%d", &n);
	polje = (float *) malloc(sizeof(float)*n);
	if(polje == NULL){
		printf("\nNema dovoljno memorije.");
	}	else	{
		for(i=0; i<n; i++){
			scanf("%f", (polje+i));
			
		}
		ispis(polje, n);
	}
	free(polje);
	return 0;
}
