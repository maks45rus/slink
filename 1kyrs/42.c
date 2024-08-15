#include <stdio.h>
#include <stdlib.h>
int main() {
    float x,y,z;
    float x1,y1,z1;
    printf("x = ");
    scanf("%f",&x);
    printf("\n");
 
    printf("y = ");
    scanf("%f",&y);
    printf("\n");
    
    printf("z = ");
    scanf("%f",&z);
    printf("\n");
    
    x1=x;
    y1=y;
    z1=z;
    
    if(x>=y){
		if(x>=z){
			x=2*(x1*y1*z1);
			printf("max: x = %f\n",x);
		}else{
			z=2*(x1*y1*z1);
			printf("max: z = %f\n",z);
		}	
		if(y<=z){
			y=(x1+y1+z1)/2;
			printf("min: y = %f\n",y);
		}else{
			z=(x1+y1+z1)/2;
			printf("min: z = %f\n",z);
		}
	}else{
		if(y>=z){
			x=2*(x1*y1*z1);
			printf("max: y = %f\n",x);
		}else{
			z=2*(x1*y1*z1);
			printf("max: z = %f\n",z);
		}	
		if(x<=z){
			y=(x1+y1+z1)/2;
			printf("min: x = %f\n",y);
		}else{
			z=(x1+y1+z1)/2;
			printf("min: z = %f\n",z);
		}
    }
    
    return 0;
}

