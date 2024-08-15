#include <stdio.h>
#include <stdlib.h>
int main() {
    int x,y,z;
    printf("x = ");
    scanf("%d",&x);
    printf("\n");
 
    printf("y = ");
    scanf("%d",&y);
    printf("\n");
    
    printf("z = ");
    scanf("%d",&z);
    printf("\n");
    
    if(x>=y){
		if(x>=z) printf("max - x = %d\n",x); else printf("max - z = %d\n",z);
		if(y<=z) printf("min - y = %d\n",y); else printf("min - z = %d\n",z);
	}else{
		if(y>=z) printf("max - y = %d\n",y); else printf("max - z = %d\n",z);
		if(x<=z) printf("min - x = %d\n",x); else printf("min - z = %d\n",z);
    }
    
    return 0;
}

