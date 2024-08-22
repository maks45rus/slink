#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define PI 3.141
int main() {
    float a,b,c;

    printf("Введите значение a: ");
    scanf("%f", &a);
    printf("Введите значение b: ");
    scanf("%f", &b);
    float S,A,B,C;
    S = a*b/2;
    printf("S = %f\n", S);
	
	c = sqrt(a*a+b*b);
	printf("c = %f\n", c);
	
	A=asin(a/c)*(180.0 / PI);
	B=asin(b/c)*(180.0 / PI);
	C=asin(c/c)*(180.0 / PI);
	printf("Угол А = %f\n Угол В = %f\n Угол С = %f\n",A,B,C);
    return 0;
}

// https://www.mathedu.ru/text/boltyanskiy_gleyzer_geometriya_7-9_1998/p328/
// https://www.calc.ru/raschet-treugolnika.html
