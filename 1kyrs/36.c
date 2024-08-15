#include <stdio.h>
#include <stdlib.h>
int main() {
    int a,b,c;
    printf("a = ");
    scanf("%d",&a);
    printf("\n");
 
    printf("b = ");
    scanf("%d",&b);
    printf("\n");
    
    printf("c = ");
    scanf("%d",&c);
    printf("\n");
    
    printf("неравенство a<b<c - ");
    
    if(a<b){
		if(b<c) printf("выполняется\n"); else printf("не выполняется\n");
    }else printf("не выполняется\n");
    
    
    printf("неравенство a>=b>=c - ");
     if(a>=b){
		if(b>=c) printf("выполняется\n"); else printf("не выполняется\n");
    }else printf("не выполняется\n");
    return 0;
}

