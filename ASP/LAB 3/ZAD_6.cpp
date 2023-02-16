#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct at {
  double element;
  struct at *sljed; 
};
typedef struct at atom;

typedef struct{
	atom *vrh;
} Stog;

int dodaj (double element, Stog *stog) { 
	atom *novi; 	

	if ((novi = (atom*) malloc(sizeof(atom))) != NULL) { 
		novi->element = element; 
		novi->sljed = stog->vrh;		
		stog->vrh = novi;
		return 1;
	}
	else return 0; 	
}


int main(void){
	int i;
	Stog stog;
	srand((unsigned) time (NULL));
	for (i = 0; i <100; i++){
		if (i % 5 == 0)	printf("\n");
		if (dodaj(rand(), &stog))	printf(" %15lf", stog.vrh->element);
		else printf(" NE");
	}
	
	return 0;
}

