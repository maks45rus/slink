#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
int main() {
    float x,y,z,x1,y1,z1;
    float max, min;
    printf("x y z:\n");
    scanf("%f %f %f",&x,&y,&z);
    printf("\n");
 
    
    if((abs(x-y)<FLT_EPSILON)||(abs(x-z)<FLT_EPSILON)||(abs(z-y)<FLT_EPSILON)){
		printf("должны быть попарно различные\n");
		return 0;
	}
    
    x1=x;
    z1=z;
    y1=y;
    if((x-y) >= FLT_EPSILON){
		if((x-z) >= FLT_EPSILON) max=x; else max=z;
		if((z-y) >= FLT_EPSILON) min=y; else min=z;
	}else{
		if((y-z) >= FLT_EPSILON) max=y; else max=z;
		if((z-x) >= FLT_EPSILON) min=x; else min=z;
    }

    if(fabs(max-x)<FLT_EPSILON) x=2*(x1*y1*z1);
    if(fabs(max-y)<FLT_EPSILON) y=2*(x1*y1*z1);
    if(fabs(max-z)<FLT_EPSILON) z=2*(x1*y1*z1);
    if(fabs(min-x)<FLT_EPSILON) x=(x1+y1+z1)/2;
    if(fabs(min-y)<FLT_EPSILON) y=(x1+y1+z1)/2;
    if(fabs(min-z)<FLT_EPSILON) z=(x1+y1+z1)/2;
    
    printf("max = %f\n",max);
    printf("min = %f\n",min);
    printf("x=%f y=%f z=%f\n",x,y,z);
    return 0;
}

