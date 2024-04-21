#include <stdio.h>

int main() {
    double a, b, sum, dif, mult, del;

    printf("Введите значение a: ");
    scanf("%lf", &a);
    printf("Введите значение b: ");
    scanf("%lf", &b);

    sum = a + b;
    printf("summa: %f\n", sum);
    dif = a - b;
    printf("raznost: %f\n", dif);
    mult = a * b;
    printf("Произведение: %f\n", mult);
    
    if(b != 0) {
		del = a/b;
        printf("Отношение: %f\n", del);
    } else {
        printf("На ноль делить нельзя.\n");
    }

    return 0;
}
