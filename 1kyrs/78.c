#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(int argc, char **argv)
{
	double n, a, N, res;
	printf("a n N\n");
	scanf("%lf %lf %lf", &a, &n, &N);
	res = 1/a;
	for(int i=1; i<=n; i++){
	res = res + (1/pow(a,pow(N,i)));
	
	printf("%d - %.20lf\n", i+1, res);	
	}
	
	printf("%lf",res);
	
	return 0;
}

