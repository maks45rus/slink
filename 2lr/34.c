#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
int main() {
    float x,y,z;
    printf("x = ");
    scanf("%f",&x);
    printf("\n");
 
    printf("y = ");
    scanf("%f",&y);
    printf("\n");
    
    printf("z = ");
    scanf("%f",&z);
    printf("\n");
    float max, min;
    if((x-y) >= FLT_EPSILON){
		if((x-z) >= FLT_EPSILON) max=x; else max=z;
		if((z-y) >= FLT_EPSILON) min=y; else min=z;
	}else{
		if((y-z) >= FLT_EPSILON) max=y; else max=z;
		if((z-x) >= FLT_EPSILON) min=x; else min=z;
    }

    if(fabs(max-x)<FLT_EPSILON) printf("max: x = %f\n",x);
    if(fabs(max-y)<FLT_EPSILON) printf("max: y = %f\n",y);
    if(fabs(max-z)<FLT_EPSILON) printf("max: z = %f\n",z);
    if(fabs(min-x)<FLT_EPSILON) printf("min: x = %f\n",x);
    if(fabs(min-y)<FLT_EPSILON) printf("min: y = %f\n",y);
    if(fabs(min-z)<FLT_EPSILON) printf("min: z = %f\n",z);
    
    return 0;
}

