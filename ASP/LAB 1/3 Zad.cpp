#include <stdio.h>
#include <stdlib.h>

double pi(int n){
	
	if (n >= 1){
		if (n == 1){
			return  4*(double)1/(1+(n-1)*2) + pi (n-1);
		}	else if(n%2==0){
		return  (double)-1/(1+(n-1)*2) + pi (n-1);	
		}	 else   {
			
			return (double)1/(1+(n-1)*2) + pi (n-1); 
		}
		
	}  else  {
		return 0;
	}
}

int main(void){
	int n;
	int i;
	double *polje;
	scanf("%d", &n);
	polje = (double*) malloc(sizeof(double)*n);
	for (i=0; i<n; i++){
		*(polje + i) = pi(i+1);
		printf("\n%lf", *(polje+1));
	}
	
	return 0;
}
