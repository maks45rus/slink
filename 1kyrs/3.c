#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main() {
    float x;

    printf("Введите значение x: ");
    scanf("%f", &x);
    
    float S,V,diag1,diag2;
    S = x*x;
    printf("S = %f\n", S);
	
	V = x*x*x;
	printf("V = %f\n", V);
	
	diag1 = sqrt(x*x+x*x);
	diag2 = sqrt(diag1*diag1+x*x);
	printf("diagonal = %f\n", diag2);
	
	
    return 0;
}
// https://www.mathedu.ru/text/boltyanskiy_gleyzer_geometriya_7-9_1998/p328/
