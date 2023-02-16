#include <stdio.h>
#include <stdlib.h>

int binarnoTrazi (float *polje, int n, float x){
	if (*polje+n/2 == x){
		return n/2;
	}  else if (x < *polje+n/2) {
		binarnoTrazi(polje, n/2, x);
			
	}	 else if (x > *polje+n/2) {
		binarnoTrazi(polje+n/2, n/2, x);
	
	}	else {
		return -1;
	}
}

int main(void){
	int n, i;
	float *polje, x;
	scanf("%d %f", &n, &x);
	polje = (float*) malloc(sizeof(float)*n);
	for(i=0; i<n; i++){
		*(polje + i) = i*1.1;
	}
	printf("\n%d", binarnoTrazi(polje, n, x));
	
	return 0;
}


