#include <stdio.h>
#include <stdlib.h>
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
    
    
    
    
    if((x+y>z)&&(x+z>y)&&(y+z>x)){
		printf("Треугольник существует\n"); 
    }else{
		printf("Треугольник не существует\n");
		return 0;
	}
	

	if((x*x+y*y==z*z)||(x*x+z*z==y*y)||(y*y+z*z==x*x)){
		printf("Треугольник прямоугольный\n"); 
	}else{ 
		
		if((x*x+y*y>z*z)&&(x*x+z*z>y*y)&&(y*y+z*z>x*x)){
			printf("Треугольник остроугольный\n"); 
		}else{
			printf("Треугольник не остроугольный\n");
		} 
		
	}
	
	if((x==y)&&(y==z)){
		printf("Треугольник равносторонний\n"); 
	}else{
		if((x==y)||(x==z)||(y==z)){
			printf("Треугольник равнобедренный\n"); 
		}
	}
    
    return 0;
}

