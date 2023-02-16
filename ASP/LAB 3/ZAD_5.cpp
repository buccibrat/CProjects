#define MAXSTOG 100

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {
	int vrh;	
	double polje[MAXSTOG];
} Stog;

void init_stog (Stog *stog){
	stog->vrh = -1;
}

int dodaj (double element, Stog *stog) {
  if (stog->vrh >= MAXSTOG-1) return 0;
  stog->vrh++;
  stog->polje[stog->vrh] = element;
  return 1;                  
}



int main (void){
	int i;
	Stog stog;
	srand ((unsigned) time (NULL));
	init_stog (&stog);
	
	for (i = 0; i < 101; i++){
		if (i % 10 == 0)	printf("\n");
		if (dodaj ((double) rand(), &stog))	printf(" %2d", i);
		else	printf(" DENIED");
	}
	
	return 0;
}

