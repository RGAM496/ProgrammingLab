#include <stdio.h>

void main(){
	int samples, farmers, i, j;
	long sum, surf, animals, factor;
	scanf("%d",&samples);
	
	for (i=0;i<samples;i++){	
		scanf("%d",&farmers);
		sum=0;
		for(j=0;j<farmers;j++){
			scanf("%ld %ld %ld",&surf,&animals,&factor);
			/*
				aqui debe ir el trabajo con la 
				suma de 'premiums' de los 
				productores
			*/
		}
		printf("%ld\n",sum);
	}
}