
#include <stdlib.h>
#include <stdio.h>
#include <time.h>




struct at {
	double element;
	struct at *sljed;
};
typedef struct at atom;

typedef struct {
	atom *ulaz, *izlaz;
} Red;

void init_red(Red *red){
	red->ulaz = NULL;
	red->izlaz = NULL;
}


int DodajURed (double element, Red *red) {
	atom *novi;
	if (novi = (atom *)malloc (sizeof (atom))) {
		novi->element = element;
		novi->sljed = NULL;
		if (red->izlaz == NULL) {
			red->izlaz = novi;		
		} else {
			(red->ulaz)->sljed = novi;	
		}
		red->ulaz = novi;			
		return 1;
	}
	return 0;
}

int poljeURed(double polje[], int n, Red *red){
	srand ((unsigned) time (NULL));
	int i;
	if (n == 1){
		i = DodajURed((double)(rand() % 10), red);
		if (i == 0)	return 0;
		return 1;
	}
	poljeURed (polje, n-1, red);
	i = DodajURed((double)rand()/RAND_MAX * 10 -1, red);
	if (i == 0) return 0;
	
	return 1;	
}
void ispis	(Red *red){
	int i;
	atom *pom;
	pom = red->izlaz;
	for (i = 0; i < 10; i++){
		printf(" \n%lf", pom->element);
		pom = pom->sljed;
	}
}

int main () {
  double polje[10];			
	Red red;
	init_red(&red);
	
	poljeURed (polje, 10, &red);
	srand ((unsigned) time (NULL));
	ispis (&red);
	return 0;
}
	
