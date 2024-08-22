#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double fact(double f)
{
	double res;
	res = 1;
	for(int i=1; i<=f; i++){
		res = res*i;
	}
	return res;
	
} 

int main(int argc, char **argv)
{
	double x, n, res;
	printf("x n\n");
	scanf("%lf %lf", &x, &n);
	res = 0;
	
	int p;
	p=1;
	
	for(int i=1; i<=n; i=i+2){
		printf("%d\n",p);
		if(p==1){
			p=0;
			res = res + pow(x,i)/fact(i);
		}else{
			p=1;
			res = res - pow(x,i)/fact(i);
		}
		printf("%d - %.20lf %d\n", i, res, p);	
	}
	
	printf("%lf",res);
	
	return 0;
}

