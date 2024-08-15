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
    
    if(a==1 || a==2 || a==3)
		printf("a принадлежит интервалу (1,3)\n");
    if(b==1 || b==2 || b==3)
		printf("b принадлежит интервалу (1,3)\n");
    if(c==1 || c==2 || c==3)
		printf("c принадлежит интервалу (1,3)\n");
    if(a==0)
		printf("a слева от интервала (1,3)\n");
    if(b==0)
		printf("b слева от интервала (1,3)\n");
    if(c==0)
		printf("c слева от интервала (1,3)\n");
    if(a==4)
		printf("a справа от интервала (1,3)\n");
    if(b==4)
		printf("b справа от интервала (1,3)\n");
    if(c==4)
		printf("c справа от интервала (1,3)\n");
    
    return 0;
}

