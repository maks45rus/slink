#include <stdio.h>
#include <math.h>
#include <math.h>
#include <float.h>

int main() {
    float a, b, c, x, y,a1,b1;
    
    printf("Введите размеры кирпича (a, b, c): ");
    scanf("%f %f %f", &a, &b, &c);
    
    printf("Введите размеры отверстия (x, y): ");
    scanf("%f %f", &x, &y);
   
	float D;
	
    if (((a-b) >= FLT_EPSILON) && ((a-c) >= FLT_EPSILON)) {
        a1=b;
        b1=c;
    } else if (((b-a) >= FLT_EPSILON) && ((b-c) >= FLT_EPSILON)) {
        a1=a;
        b1=c;
    } else {
		a1=a;
		b1=b;
    }
	
	D = sqrt(a1*a1+b1*b1);
	if( ((D-x) >= FLT_EPSILON)||((D-y) >= FLT_EPSILON) ){
		printf("кирпич не войдет\n");
	}else{
		printf("кирпич войдет при любом положении\n");
	}
    
    return 0;
}
