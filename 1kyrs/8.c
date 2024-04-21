#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141
int main() {
    float r,n;

    printf("Введите значение n: ");
    scanf("%f", &n);
    printf("Введите значение r: ");
    scanf("%f", &r);
    float Pout,Pin,a;
    a=(180/n)/(180.0 / PI);
    Pout = 2*n*r*tan(a);
	printf("Pout = %f\n",Pout);
	
	Pin = 2*n*r*sin(a);
    printf("Pin = %f\n",Pin);
	
    return 0;
}

// https://www.mathedu.ru/text/boltyanskiy_gleyzer_geometriya_7-9_1998/p328/

