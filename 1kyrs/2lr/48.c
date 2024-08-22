#include <stdio.h>
#include <math.h>
#include <float.h>

int main() {
    float a, b, c;
    float D, x1, x2;
	
    printf("Введите значения a, b, c: ");
    scanf("%f %f %f", &a, &b, &c);

    D = b*b - 4*a*c;

    if (D > FLT_EPSILON) {
		printf("2 корня.\n");
        x1 = (-b + sqrt(D)) / (2*a);
        x2 = (-b - sqrt(D)) / (2*a);
        printf("Действительные корни: x1 = %f, x2 = %f\n", x1, x2);
    } else if (D < -FLT_EPSILON){
		printf("0 корней.\n");
        printf("Действительных корней нет.\n");
    } else {
		printf("1 корень.\n");
        x1 = -b/(2*a);
        printf("Действительный корень: x = %f\n", x1);
    }

    return 0;
}
