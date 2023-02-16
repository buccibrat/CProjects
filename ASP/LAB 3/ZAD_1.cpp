#include <stdio.h>
#include <stdlib.h>

struct cvor{
	float element;
	struct cvor *sljed;
};
	typedef struct cvor cvor;

int upis(cvor **glava, cvor **rep, float broj){
	cvor *pom;
	if(!(pom = (cvor *) malloc(sizeof (cvor))))	return 0;
	if (*glava == NULL){
		pom->element = broj;	
		*glava = pom;
		*rep = pom;
		return 1;
	}
	pom->element = broj;
	(*rep)->sljed = pom;
	*rep=pom;
	return 1;	
}

void ispis_brisi(cvor **glava){
	cvor *pom;
	pom = *glava;
	*glava = (*glava)->sljed;
	printf("%f ", pom->element);
	free(pom);
}

int main(void){
	int n, i;
	cvor *glava = NULL, *rep = NULL;
	float broj;
	do {
		scanf("%d", &n);
	}	while (n <= 1 && n >= 10);

	for (i = 0; i < n; i++){
		scanf("%f", &broj);
		upis (&glava, &rep, broj);		
	}
	for (i = 0; i < n; i++){
		ispis_brisi(&glava);
	}
	
	return 0;
}







