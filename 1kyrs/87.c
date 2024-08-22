#include <stdio.h>
#include <stdlib.h>
#include <math.h>



int main(int argc, char **argv)
{
	int n, m, res;
	printf("n m\n");
	scanf("%d %d", &n, &m);
	res = 0;
	
	
	while(m!=0){
		res = res + n%10;
		n = n/10;
		m--;
	}
	
	
	printf("res = %d\n",res);

	return 0;
}

