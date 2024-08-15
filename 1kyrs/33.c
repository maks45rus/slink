#include <stdio.h>
#include <stdlib.h>
int main() {
    int x,y;
    printf("x = ");
    scanf("%d",&x);
    printf("\n");
 
    printf("y = ");
    scanf("%d",&y);
    printf("\n");
    
    if(x>=y){
		printf("max - x = %d\n",x);
		printf("min - y = %d\n",y);
		
	}else{
		printf("max - y = %d\n",y);
		printf("min - x = %d\n",x);
    }
    return 0;
}

