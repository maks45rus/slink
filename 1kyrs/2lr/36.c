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
    
    printf("неравенство a<b<c - ");
    
    if((b-a) >= FLT_EPSILON){
		if((c-b) >= FLT_EPSILON) printf("выполняется\n"); else printf("не выполняется\n");
    }else printf("не выполняется\n");
    
    
    printf("неравенство a>=b>=c - ");
     if( !((b-a) >= FLT_EPSILON) ){
		if( !((c-b) >= FLT_EPSILON) ) printf("выполняется\n"); else printf("не выполняется\n");
    }else printf("не выполняется\n");
    
     printf("неравенство a<=b<=c - ");
     if( !((a-b) >= FLT_EPSILON) ){
		if( !((b-c) >= FLT_EPSILON) ) printf("выполняется\n"); else printf("не выполняется\n");
    }else printf("не выполняется\n");
    return 0;
}

