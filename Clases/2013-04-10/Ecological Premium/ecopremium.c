#include <stdio.h>

int main(){
	int samples, farmers, i, j;
	long sum, surf, animals, factor;
	scanf("%d",&samples);
	
	for (i=0;i<samples;i++){	
		scanf("%d",&farmers);
		sum=0;
		for(j=0;j<farmers;j++){
			scanf("%ld %ld %ld",&surf,&animals,&factor);
			sum += surf * factor; /* (surf / animal) * animal == surf */
		}
		printf("%ld\n",sum);
	}
}