#include <stdio.h>
#include <stdlib.h>

struct cvor	{
	double element;
	struct cvor *sljed;
};	typedef struct cvor cvor;

typedef struct {
	cvor *ulaz, *izlaz;
} Red;

void init_red	(Red **red){
	(*red)->ulaz = NULL;
	(*red)->izlaz = NULL;
}

int dodajURed	(double broj, Red **red){
	cvor *novi;
	if (novi = (cvor *) malloc (sizeof (cvor))) {
		novi->element = broj;
		novi->sljed = NULL;
		if ((*red)->izlaz == NULL) {
			(*red)->izlaz = novi;		
		} else {
			((*red)->ulaz)->sljed = novi;	
		}
		(*red)->ulaz = novi;			
		return 1;
	}
	return 0;
}

int main(void){
	double broj;
	int n, i;
	Red *red;
	
	init_red (&red);
	
	scanf("%d", &n);
	for (i = 0; i < n; i++){
		scanf("%lf", &broj);
		if(dodajURed(broj, &red)){
			printf(" %lf", broj);
		}
			
	}
	return 0;	
}







