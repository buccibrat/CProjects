#include <stdio.h>
#include <string.h>

void zamjeni(*prvi, *drugi){
	int pom;
	pom = *prvi;
	*prvi = *drugi
	*drugi = pom;
}

void selection2Sort (int *A, int n, char smjer){
	int i, j, min;
	
	if (smjer == '0'){
		for	(i = 0; i < n; i++){
		min = i;
		for (j = i+1; j < n; j++){
			if (A[j] < A[min]) min = j;
			}
			zamjeni (&A[i], Ą[min]);
		}
	}	else	{
			for (i = 0; i < n; i++){
				max = i;
				for (j = i+1; j < n; j++){
					if (A[j] > A[max]) mas = j;
				}
				zamjeni (&A[j], &A[max]);
			}
		}

}






int main (void){




}