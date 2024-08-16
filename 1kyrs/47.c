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
    
    
    
    
    if((x+y-z>FLT_EPSILON)&&(x+z-y>FLT_EPSILON)&&(y+z-x>FLT_EPSILON)){
		printf("Треугольник существует\n"); 
    }else{
		printf("Треугольник не существует\n");
		return 0;
	}
	


	if((x*x+y*y-z*z>=FLT_EPSILON)&&(x*x+z*z-y*y>=FLT_EPSILON)&&(y*y+z*z-x*x>=FLT_EPSILON)){
		printf("Треугольник остроугольный\n"); 
	}else if((x*x+y*y-z*z<=-FLT_EPSILON)||(x*x+z*z-y*y<=-FLT_EPSILON)||(y*y+z*z-x*x<=-FLT_EPSILON)){
		printf("Треугольник не остроугольный\n");
	}else{
		printf("Треугольник прямоугольный\n");
	} 
		
	
	if((abs(x-y)<FLT_EPSILON)&&(abs(y-z)<FLT_EPSILON)){
		printf("Треугольник равносторонний\n"); 
	}else{
		if((abs(x-y)<FLT_EPSILON)||(abs(y-z)<FLT_EPSILON)||(abs(y-z)<FLT_EPSILON)){
			printf("Треугольник равнобедренный\n"); 
		}
	}
    
    return 0;
}

