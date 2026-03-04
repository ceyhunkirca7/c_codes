#include <stdio.h>
#include <stdlib.h>


int main() {
	

	int sayac=0,p,q,N;
	scanf("%d",&N);
	
	for(p=0;p<=N;p++)
	{for(q=p+1;q<=N-p;q++)
	{
		sayac=sayac +1;
	}
	}
	
	printf("%d",sayac);
	return 0;
}
