#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
int main() {
    float x, y, z, s;

    
    scanf("%f %f %f", &x, &y, &z);

    if((abs(x-y)<FLT_EPSILON)||(abs(x-z)<FLT_EPSILON)||(abs(z-y)<FLT_EPSILON)){
		printf("должны быть попарно различные\n");
		return 0;
	}
    

    if((y-x) >= FLT_EPSILON){
        if((z-x) >= FLT_EPSILON){
            s = x;
        }else{
            s = z;
        }
    } else {
        if((z-y) >= FLT_EPSILON){
            s = y;
        }else{
            s = z;
        }
    }
    
    if (( 1 - (x + y + z)) >= FLT_EPSILON) {
        
        if (abs(s-x) < FLT_EPSILON) {
            x = (y + z) / 2;
        }else if (abs(s-y) < FLT_EPSILON) {
            y = (x + z) / 2;
        }else{
            z = (x + y) / 2;
        }
    } else {
        if ((y-x) >= FLT_EPSILON) {
            x = (y + z) / 2;
        } else {
            y = (x + z) / 2;
        }
    }

    printf("x = %f, y = %f, z = %f\n", x, y, z);

    return 0;
}
