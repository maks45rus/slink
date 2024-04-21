#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float x,y;

    printf("Введите значение x: ");
    scanf("%f", &x);
    printf("Введите значение y: ");
    scanf("%f", &y);
	
	float res;
	
	res = (fabs(x) - fabs(y)) / (1 + fabs(x * y));
	printf("result = %f\n",res);
	
	
	res = (x-y)/(1+x*y);
	printf("result = %f",res);
    return 0;
}
