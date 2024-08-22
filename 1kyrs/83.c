#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(int argc, char **argv)
{
	double a, res;
	printf("a\n");
	scanf("%lf", &a);
	res = 0;
	
	res = 0;
	double i = 1;
	
	while(res <= a){
		
		res = res + 1/i;
		i++;
	}
	
	
	printf("res = %lf\n",res);
	
	//Б
	printf("n = %lf\n",i-1);
	return 0;
}

