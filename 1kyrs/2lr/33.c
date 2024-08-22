#include <stdio.h>
#include <stdlib.h>
#include <float.h>
int main() {
    float x,y;
    printf("x = ");
    scanf("%f",&x);
    printf("\n");
 
    printf("y = ");
    scanf("%f",&y);
    printf("\n");
    
    if ((x - y) > FLT_EPSILON) {
        printf("max - x = %f\n", x);
        printf("min - y = %f\n", y);
    } else if ((x - y) < -FLT_EPSILON) {
        printf("max - y = %f\n", y);
        printf("min - x = %f\n", x);
    } else {
        printf("max - x = %f и y = %f\n", x, y);
        printf("min - x = %f и y = %f\n", x, y);
    }
    return 0;
}

