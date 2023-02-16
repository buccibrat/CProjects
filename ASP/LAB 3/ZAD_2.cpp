#define MAXRED 10

#include <stdio.h>

typedef struct {
	double polje[MAXRED]; 
	int ulaz, izlaz;
} Red;
 
 void init_red (Red *red){
 	red->ulaz = 0;
 	red->izlaz = 0;
 }

int dodajURed (double broj, Red *red){
 if ((red->ulaz+1) % MAXRED == red->izlaz) return 0;
 red->ulaz++; 
 red->ulaz %= MAXRED;
 red->polje[red->ulaz] = broj;
 return 1;
}



int skiniIzReda (double *broj, Red *red){
  if (red->ulaz == red->izlaz) return 0;
  red->izlaz++; 
  red->izlaz %= MAXRED;
  *broj = red->polje[red->izlaz];
  return 1;
}



int main (void){
	int n, i;
	double broj;
	double *temp;
	Red red;
	
	init_red(&red);
	
	scanf ("%d", &n);
	for (i = 0; i < n; i++){
		scanf("%lf", &broj);
		dodajURed(broj, &red);
	}
	temp = &broj;
	for (i = 0; i < n; i++){
		skiniIzReda(temp, &red);
		printf("%lf", *temp);
	}
	
	return 0;	
}
