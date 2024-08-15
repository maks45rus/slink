#include <stdio.h>
#include <stdlib.h>
int main() {
    float x, y, z, s;

    
    scanf("%f %f %f", &x, &y, &z);

    
    

    if (x < y) {
        if (x < z) {
            s = x;
        } else {
            s = z;
        }
    } else {
        if (y < z) {
            s = y;
        } else {
            s = z;
        }
    }
    
    if (x + y + z < 1) {
        
        if (s == x) {
            x = (y + z) / 2;
        }else if (s == y) {
            y = (x + z) / 2;
        }else{
            z = (x + y) / 2;
        }
    } else {
        if (x < y) {
            x = (y + z) / 2;
        } else {
            y = (x + z) / 2;
        }
    }

    printf("x = %f, y = %f, z = %f\n", x, y, z);

    return 0;
}
