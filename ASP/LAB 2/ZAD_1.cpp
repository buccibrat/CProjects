#include <stdio.h>
#include <stdlib.h>

struct zapis{
	int pBroj;
	char mjesto [40+1];
};
typedef struct zapis atom;


void insertionSort(atom *a, int n, char smjer){
	int i, j;
	int pom;
	
	if (smjer == '0'){
		for(i = 1; i < n; i++){
			pom = (*(a+i)).pBroj;
			for (j = i; j >= 1 && (*(a+j-1)).pBroj > pom; j--){
				(*(a+j)).pBroj = (*(a+j-1)).pBroj;
			}
			(*(a+j)).pBroj = pom;
		}	
	}
	
	if (smjer == '1'){
		for (i = 1; i < n; i++){
			pom = (*(a+i)).pBroj;
			for (j = i; j >= 1 && (*(a+j-1)).pBroj < pom; j--){
				(*(a+j)).pBroj = (*(a+j-1)).pBroj;
			}
			(*(a+j)).pBroj = pom;
		}	
	}
}


int main (void){
	int n, i;
	char smjer;
	atom *p;
	scanf("%d", &n);
	 
	p = (atom *) malloc (sizeof(atom) * n);
	scanf("%s", &smjer);
	for(i = 0; i < n; i++){
		scanf("%d", &(*(p+i)).pBroj);
		scanf("%s", &(*(p+i)).mjesto);
	}
	insertionSort(p, n, smjer);
	printf("\n");
	for(i = 0; i < n; i++){
		printf("\n%d %s", (*(p+i)).pBroj, (*(p+i)).mjesto);
	}
	
	return 0;
}









