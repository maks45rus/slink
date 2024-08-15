#include <stdio.h>
#include <math.h>

int main() {
    float a, b, c, x, y,x1,x2;
    
    printf("Введите размеры кирпича (a, b, c): ");
    scanf("%f %f %f", &a, &b, &c);
    
    printf("Введите размеры отверстия (x, y): ");
    scanf("%f %f", &x, &y);
   

    if (a >= b && a >= c) {
        x1=b;
        x2=c;
    } else if (b >= a && b >= c) {
        x1=a;
        x2=c;
    } else {
		x1=a;
		x2=b;
    }

	float z;
	if(x1<x2){
	z=sqrt((x1*x1)/2);
	}

    return 0;
}
    
    return 0;
}
