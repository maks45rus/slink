#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	double n, N, res;
	printf("n N\n");
	scanf("%lf %lf", &n, &N);
	res = 0;
	for(int i=0; i<n; i++){
	res = sqrt(N + res);
	//printf("%d - %lf\n", i+1, res);	
	}
	
	printf("%lf",res);
	
	return 0;
}

