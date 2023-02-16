#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAXSTOG 10

struct st{
	double polje[MAXSTOG];
	int vrh;
};
typedef struct st Stog;

void init_stog	(Stog *stog){
	stog->vrh = -1;
}

int dodaj(Stog *stog, double broj){
	if (stog->vrh >= MAXSTOG-1)	return 0;
	stog->vrh++;
	stog->polje[stog->vrh] = broj;
	return 1;
}

int skini(Stog *stog, double *broj){
	if (stog->vrh < 0)	return 0;
	*broj = stog->polje[stog->vrh];
	stog->vrh--;
	return 1;
}
