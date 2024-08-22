#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <float.h>
int main() {
    float a,b,c;
    printf("a = ");
    scanf("%f",&a);
    printf("\n");
 
    printf("b = ");
    scanf("%f",&b);
    printf("\n");
    
    printf("c = ");
    scanf("%f",&c);
    printf("\n");
    
    if(((a-1) >= FLT_EPSILON)&&((3-a) >= FLT_EPSILON))
		printf("a принадлежит интервалу (1,3)\n");
    if(((b-1) >= FLT_EPSILON)&&((3-b) >= FLT_EPSILON))
		printf("b принадлежит интервалу (1,3)\n");
    if(((c-1) >= FLT_EPSILON)&&((3-c) >= FLT_EPSILON))
		printf("c принадлежит интервалу (1,3)\n");
    if( !((a-1) >= FLT_EPSILON) )
		printf("a слева от интервала (1,3)\n");
    if( !((b-1) >= FLT_EPSILON) )
		printf("b слева от интервала (1,3)\n");
    if( !((c-1) >= FLT_EPSILON) )
		printf("c слева от интервала (1,3)\n");
    if( !((3-a) >= FLT_EPSILON) )
		printf("a справа от интервала (1,3)\n");
    if( !((3-b) >= FLT_EPSILON) )
		printf("b справа от интервала (1,3)\n");
    if( !((3-c) >= FLT_EPSILON) )
		printf("c справа от интервала (1,3)\n");
    
    return 0;
}

